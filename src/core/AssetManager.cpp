#include "core/AssetManager.hpp"
#include "Config.hpp"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <vector>

AssetManager::AssetManager()
{
    std::filesystem::path file;
    std::filesystem::path dir;
    auto GetPath = [&]() { return dir / file; };

    // texturepacks
    /*
    "textures": [
        "texturepack_0.png"
    ],
    "sprites": {
        "gui_tab_vehicles": {
            "texture_id": 0,
            "x": 3,
            "y": 3,
            "w": 122,
            "h": 70,
            "ox": 0.5,
            "oy": 0.5
        },...
    */
    file = "texturepack.json";
    dir = game::config::path::TP;
    std::ifstream f(GetPath());
    nlohmann::json data = nlohmann::json::parse(f);

    // load textures
    std::vector<Texture2D*> texturesByID;
    for (size_t i = 0; i < data["textures"].size(); i++)
    {
        auto fn = data["textures"][i].get<std::string>();
        m_textures[fn] = LoadTexture(GetPath().c_str());
        SetTextureFilter(m_textures[fn], TEXTURE_FILTER_BILINEAR);
        texturesByID[i] = &m_textures[fn];
    }

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

    m_font = LoadFontEx(game::config::path::Font, 32, nullptr, 0);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
}

AssetManager::~AssetManager()
{
    // unload all textures
    for (auto& [name, texture] : m_textures)
    {
        UnloadTexture(texture);
    }

    UnloadFont(m_font);
}

Sprite* AssetManager::GetSprite(const std::string& spriteName)
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
    {
        return &it->second;
    }

    return nullptr;
}

SpriteNP* AssetManager::GetSpriteNP(const std::string& spriteName)
{
    auto it = m_spritesNP.find(spriteName);
    if (it != m_spritesNP.end())
    {
        return &it->second;
    }

    return nullptr;
}
Font AssetManager::GetFont() { return m_font; }