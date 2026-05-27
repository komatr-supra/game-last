#include "core/AssetManager.hpp"
#include "Config.hpp"
#include "json.hpp"
#include <fstream>

AssetManager::AssetManager()
{
    TraceLog(LOG_ERROR, "asset manager started");
    std::ifstream f(Config::FilePaths::TexturePack);
    nlohmann::json data = nlohmann::json::parse(f);
    TraceLog(LOG_ERROR, "reading texturepack jsno file");
    std::string texturePath = data["meta"]["image"];
    TraceLog(LOG_ERROR, "texture path readed: %s", texturePath.c_str());
    texturePath = "data/" + texturePath;
    m_texture = LoadTexture(texturePath.c_str());
    for (auto& [name, frameData] : data["frames"].items())
    {
        Sprite sprite;

        sprite.name = name;

        sprite.texture = m_texture;

        sprite.sourceRect = Rectangle{frameData["frame"]["x"],
                                      frameData["frame"]["y"],
                                      frameData["frame"]["w"],
                                      frameData["frame"]["h"]};

        int offsetX = frameData["spriteSourceSize"]["x"];
        int offsetY = frameData["spriteSourceSize"]["y"];

        int originalWidth = frameData["sourceSize"]["w"];
        int originalHeight = frameData["sourceSize"]["h"];

        float pivotRelativeX = frameData["pivot"]["x"];
        float pivotRelativeY = frameData["pivot"]["y"];

        float pivotX = (originalWidth * pivotRelativeX) - offsetX;
        float pivotY = (originalHeight * pivotRelativeY) - offsetY;

        sprite.origin = Vector2{pivotX, pivotY};

        m_sprites[name] = sprite;
        TraceLog(LOG_ERROR, "Sprite %s was created and added to the sprites collection.", name.c_str());
    }

    Sprite9Slice bg;
    bg.texture = LoadTexture("data/background color.png");
    SetTextureFilter(bg.texture, TEXTURE_FILTER_BILINEAR);
    bg.nPatchInfo.source = {0, 0, (float)bg.texture.width, (float)bg.texture.height};
    bg.nPatchInfo.right = 6;
    bg.nPatchInfo.top = 6;
    bg.nPatchInfo.left = 6;
    bg.nPatchInfo.bottom = 6;
    bg.nPatchInfo.layout = NPATCH_NINE_PATCH;
    m_spritesNP["background color"] = bg;

    Sprite9Slice bgb;
    bgb.texture = LoadTexture("data/background border.png");
    SetTextureFilter(bgb.texture, TEXTURE_FILTER_BILINEAR);
    bgb.nPatchInfo.source = {0, 0, (float)bgb.texture.width, (float)bgb.texture.height};
    bgb.nPatchInfo.right = 6;
    bgb.nPatchInfo.top = 6;
    bgb.nPatchInfo.left = 6;
    bgb.nPatchInfo.bottom = 6;
    bgb.nPatchInfo.layout = NPATCH_NINE_PATCH;
    m_spritesNP["background border"] = bgb;

    Sprite9Slice line;
    line.texture = LoadTexture("data/line.png");
    SetTextureFilter(line.texture, TEXTURE_FILTER_BILINEAR);
    line.nPatchInfo.source = {0, 0, (float)line.texture.width, (float)line.texture.height};
    line.nPatchInfo.right = 4;
    line.nPatchInfo.left = 4;
    line.nPatchInfo.layout = NPATCH_THREE_PATCH_HORIZONTAL;
    m_spritesNP["line horizontal"] = line;

    m_font = LoadFontEx("data/Lato-Regular.ttf", 32, nullptr, 0);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);

    Sprite icon;
    icon.texture = LoadTexture("data/gui_vehicles.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites["tab vehicles"] = icon;

    icon.texture = LoadTexture("data/gui_mainfests.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites["tab mainfests"] = icon;

    icon.texture = LoadTexture("data/gui_marketplace.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites["tab marketplace"] = icon;

    icon.texture = LoadTexture("data/gui_sabotages.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites["tab sabotages"] = icon;

    icon.texture = LoadTexture("data/icon plus.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites["icon plus"] = icon;
}

AssetManager::~AssetManager()
{
    // unload all textures
    UnloadTexture(m_texture);
    UnloadFont(m_font);
}

Sprite AssetManager::GetSprite(const std::string& spriteName)
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
    {
        return it->second;
    }

    return Sprite();
}

Sprite9Slice AssetManager::GetSpriteNP(const std::string& spriteName)
{
    auto it = m_spritesNP.find(spriteName);
    if (it != m_spritesNP.end())
    {
        return it->second;
    }

    return Sprite9Slice();
}
Font AssetManager::GetFont() { return m_font; }