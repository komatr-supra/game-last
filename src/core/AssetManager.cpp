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

    m_guiPanel.name = "panel_gui";
    m_guiPanel.texture = LoadTexture("data/window.png");
    m_guiPanel.nPatchInfo.source = {0, 0, (float)m_guiPanel.texture.width, (float)m_guiPanel.texture.height};
    m_guiPanel.nPatchInfo.right = 8;
    m_guiPanel.nPatchInfo.top = 8;
    m_guiPanel.nPatchInfo.left = 8;
    m_guiPanel.nPatchInfo.bottom = 8;
    m_guiPanel.nPatchInfo.layout = NPATCH_NINE_PATCH;

    m_font = LoadFontEx(Config::FilePaths::Font, 48, nullptr, 0);

    Sprite icon;
    icon.name = "gui_tab_vehicles";
    icon.texture = LoadTexture("data/gui_vehicles.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites[icon.name] = icon;

    icon.name = "gui_tab_mainfests";
    icon.texture = LoadTexture("data/gui_mainfests.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites[icon.name] = icon;

    icon.name = "gui_tab_marketplace";
    icon.texture = LoadTexture("data/gui_marketplace.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites[icon.name] = icon;

    icon.name = "gui_tab_sabotages";
    icon.texture = LoadTexture("data/gui_sabotages.png");
    icon.origin = {(float)icon.texture.width / 2, (float)icon.texture.height / 2};
    icon.sourceRect = {0, 0, (float)icon.texture.width, (float)icon.texture.height};
    m_sprites[icon.name] = icon;
}

AssetManager::~AssetManager()
{
    // unload all textures
    UnloadTexture(m_texture);
    UnloadTexture(m_guiPanel.texture);
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

Sprite9Slice AssetManager::GetGuiPanel() { return m_guiPanel; }
Font AssetManager::GetFont() { return m_font; }