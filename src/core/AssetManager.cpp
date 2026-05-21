#include "Config.hpp"

#include "core/AssetManager.hpp"

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
}

AssetManager::~AssetManager() {}

Sprite AssetManager::GetSprite(const std::string& spriteName)
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
    {
        return it->second;
    }

    return Sprite();
}