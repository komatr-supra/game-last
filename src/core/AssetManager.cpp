#include "core/AssetManager.hpp"
#include "Config.hpp"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <vector>

AssetManager::AssetManager()
{
    // BACKUP ASSETS - loaded at all cast... also looking inside assets in project folder
    // TODO: remove at production
    m_errorTexture = LoadTexture("../assets/thumb-down.png");
    m_errorSprite.texture = &m_errorTexture;
    m_errorSprite.origin = {0.5f, 0.5f};
    m_errorSprite.sourceRect = {0, 0, (float)m_errorTexture.width, (float)m_errorTexture.height};
    m_errorSpriteNP.texture = &m_errorTexture;
    m_errorSpriteNP.nPatchInfo.layout = NPATCH_NINE_PATCH;
    m_errorSpriteNP.nPatchInfo.source = m_errorSprite.sourceRect;
    // FONT
    m_font = LoadFontEx(game::constant::path::Font, 32, nullptr, 0);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
    // TEXTUREPACK
    std::filesystem::path file;
    std::filesystem::path dir;
    auto GetPath = [&]() { return dir / file; };
    file = "texturepack.json";
    dir = game::constant::path::TP;
    std::ifstream f(GetPath());
    nlohmann::json data = nlohmann::json::parse(f);
    // TEXTURES
    std::vector<Texture2D*> texturesByID;
    for (size_t i = 0; i < data["textures"].size(); i++)
    {
        auto fn = data["textures"][i].get<std::string>();
        m_textures[fn] = LoadTexture(GetPath().c_str());
        SetTextureFilter(m_textures[fn], TEXTURE_FILTER_BILINEAR);
        texturesByID[i] = &m_textures[fn];
    }
    // SPRITES
    for (auto& [name, sprData] : data["sprites"].items())
    {
        if (sprData.contains("slice"))
        {
            SpriteNP spriteNP;
            spriteNP.texture = texturesByID[sprData["texture_id"]];
            spriteNP.nPatchInfo.source = {sprData["x"], sprData["y"], sprData["w"], sprData["h"]};

            auto slice = sprData["slice"];
            spriteNP.nPatchInfo.right = slice["r"];
            spriteNP.nPatchInfo.top = slice["t"];
            spriteNP.nPatchInfo.left = slice["l"];
            spriteNP.nPatchInfo.bottom = slice["b"];
            if (spriteNP.nPatchInfo.right == 0 && spriteNP.nPatchInfo.left == 0)
                spriteNP.nPatchInfo.layout = NPATCH_THREE_PATCH_VERTICAL;
            else if (spriteNP.nPatchInfo.top == 0 && spriteNP.nPatchInfo.bottom == 0)
                spriteNP.nPatchInfo.layout = NPATCH_THREE_PATCH_HORIZONTAL;
            else
                spriteNP.nPatchInfo.layout = NPATCH_NINE_PATCH;

            m_spritesNP[name] = spriteNP;
        }
        else
        {
            Sprite sprite;
            sprite.texture = texturesByID[sprData["texture_id"]];
            sprite.sourceRect = {sprData["x"], sprData["y"], sprData["w"], sprData["h"]};
            sprite.origin = {sprData["ox"], sprData["oy"]};

            m_sprites[name] = sprite;
        }
    }
}

AssetManager::~AssetManager()
{
    // unload ALL
    UnloadFont(m_font);
    UnloadTexture(m_errorTexture);
    for (auto& [name, texture] : m_textures)
        UnloadTexture(texture);
}

const Sprite& AssetManager::GetSprite(const std::string& spriteName)
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
        return it->second;

    return m_errorSprite;
}

const SpriteNP& AssetManager::GetSpriteNP(const std::string& spriteName)
{
    auto it = m_spritesNP.find(spriteName);
    if (it != m_spritesNP.end())
        return it->second;

    return m_errorSpriteNP;
}
Font AssetManager::GetFont() { return m_font; }