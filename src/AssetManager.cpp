#include "AssetManager.hpp"
#include "Config.hpp"
#include "Sprite.hpp"
#include "json.hpp"
#include "raylib.h"
#include "vehicle/Vehicle.hpp"
#include "vehicle/VehicleDefinition.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace game::assets
{
namespace fs = std::filesystem;

AssetManager::AssetManager()
{
    // FALLBACK ASSETS
    TraceLog(LOG_INFO, "Loading fallback assets...");
    Texture2D texture = LoadTexture(game::constant::path::FallbackTexture);
    if (IsTextureValid(texture))
    {
        m_textures[fallback] = texture;
        auto s = Sprite{&m_textures.at(fallback)};
        s.origin = {0.5f, 0.5f};
        s.sourceRect = {0, 0, 64, 64};
        m_sprites.emplace(fallback, s);
        m_spritesNP[fallback] = {&m_textures[fallback], {{0, 0, 64, 64}, 4, 4, 4, 4, NPATCH_NINE_PATCH}};

        m_models.push_back(LoadModelFromMesh(GenMeshCube(2, 2, 2)));
        m_models[m_models.size() - 1].materials[0].maps[MATERIAL_MAP_ALBEDO].texture = texture;
        TraceLog(LOG_INFO, "SUCCESS");
    }
    else
    {
        throw std::runtime_error("FALLBACK assets loading FAILED!");
    }

    // MAP
    TraceLog(LOG_INFO, "Loading Map plane and Map texture...");
    Mesh terrainMesh = GenMeshPlane(game::constant::settings::mapSizeX, game::constant::settings::mapSizeY, 1, 1);
    m_models.push_back(LoadModelFromMesh(terrainMesh));
    size_t mapModelID = m_models.size() - 1;
    m_nameToModelID["map"] = mapModelID;
    auto map = LoadTexture(game::constant::path::Map);
    SetTextureFilter(map, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(map, TEXTURE_WRAP_CLAMP);
    m_models[mapModelID].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = map;
    if (IsTextureValid(map) && IsModelValid(m_models[mapModelID]))
        TraceLog(LOG_INFO, "SUCCESS");
    else
        throw std::runtime_error("Map Plane loading FAILED!");

    // FONT
    TraceLog(LOG_INFO, "Loading font...");
    m_font = LoadFontEx(game::constant::path::Font, 32, nullptr, 0);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
    if (IsFontValid(m_font))
        TraceLog(LOG_INFO, "Font loading ... SUCCESS");
    else
    {
        TraceLog(LOG_ERROR, "Font loading FAILED");
        TraceLog(LOG_WARNING, "Using default font");
        m_font = GetFontDefault();
    }

    // TEXTUREPACK
    TraceLog(LOG_INFO, "Loading Textures...");
    TraceLog(LOG_INFO, "Opening texture json file: %s", game::constant::path::TP);
    std::ifstream f(game::constant::path::TP);
    if (!f.is_open())
    {
        throw std::runtime_error("Texturepack file open FAILED!");
    }
    TraceLog(LOG_INFO, "Parsing json file...");
    nlohmann::json data = nlohmann::json::parse(f, nullptr, false);
    TraceLog(LOG_INFO, "Closing json file");
    f.close();
    if (data.is_discarded())
    {
        throw std::runtime_error("Json file for texturepack can't be parsed - file exist, but can't read.");
    }

    // TEXTURES
    std::vector<Texture2D*> texturesByID; // relative indexed textures - for sprite parse
    for (size_t i = 0; i < data["textures"].size(); i++)
    {
        fs::path path = game::constant::path::TP;
        fs::path textureName = data["textures"][i].get<std::string>();
        path = path.remove_filename() / textureName;
        TraceLog(LOG_INFO, "texture path is: %s", (path).c_str());
        auto tex = LoadTexture(path.c_str());
        if (!IsTextureValid(tex))
        {
            TraceLog(LOG_ERROR, "Loading texture: %s ... !!!FAILED!!!", path.c_str());
        }
        else
        {
            m_textures[textureName] = tex;
            SetTextureFilter(m_textures[textureName], TEXTURE_FILTER_BILINEAR);
            texturesByID.push_back(&m_textures[textureName]);
        }
    }
    TraceLog(LOG_INFO, "Loading Textures ... SUCCESS");

    // SPRITES
    TraceLog(LOG_INFO, "Loading Sprites");
    for (auto& [name, sprData] : data["sprites"].items())
    {
        // is this sprite 9slice variant?
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
            int textureId = sprData["texture_id"];
            TraceLog(LOG_WARNING, "texture id is: %d", textureId);
            Sprite sprite{texturesByID[textureId]};
            sprite.sourceRect = {sprData["x"], sprData["y"], sprData["w"], sprData["h"]};
            sprite.origin = {sprData["ox"], sprData["oy"]};
            TraceLog(LOG_WARNING, "sprite created: %s", name.c_str());
            m_sprites.emplace(name, sprite);
        }
    }
    TraceLog(LOG_INFO, "Loading sprites ... SUCCESS");

    // MODELS
    TraceLog(LOG_INFO, "Loading models");
    // open file, parse, save
    // TODO: create DataLoader -> move everything inside
    std::ifstream file(game::constant::path::VehicleDatabase);
    nlohmann::json dataVehiclesJSON = nlohmann::json::parse(file);
    if (dataVehiclesJSON.is_discarded())
    {
        throw std::runtime_error("Json file for texturepack can't be parsed - file exist, but can't read.");
    }
    for (auto& vehicleJSON : dataVehiclesJSON["vehicles"])
    {
        TraceLog(LOG_INFO, "Vehicle in database");
        game::vehicles::CarType carType = GetCarType(vehicleJSON["type"].get<std::string>());
        m_vehicleDatabase[carType] =
            std::make_unique<game::vehicles::VehicleDefinition>(vehicleJSON["name"].get<std::string>(),
                                                                carType,
                                                                vehicleJSON["maxSpeed"].get<int>(),
                                                                vehicleJSON["maxCapacity"].get<int>(),
                                                                vehicleJSON["price"].get<int>(),
                                                                GetSprite(vehicleJSON["resource"].get<std::string>()),
                                                                GetModelID(vehicleJSON["resource"].get<std::string>()));
        TraceLog(LOG_INFO, "Vehicle \"%s\" in database CREATED", vehicleJSON["name"].get<std::string>().c_str());
    }
}

AssetManager::~AssetManager()
{
    // unload ALL
    UnloadFont(m_font);
    for (auto& [name, texture] : m_textures)
        UnloadTexture(texture);
    for (auto& model : m_models)
        UnloadModel(model);
}

const Sprite& AssetManager::GetSprite(const std::string& spriteName) const
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end())
    {
        return it->second;
    }

    return m_sprites.at(fallback);
}

const SpriteNP& AssetManager::GetSpriteNP(const std::string& spriteName) const
{
    auto it = m_spritesNP.find(spriteName);
    if (it != m_spritesNP.end())
    {
        return it->second;
    }
    return m_spritesNP.at(fallback);
}
size_t AssetManager::GetModelID(const std::string& name3Dmodel)
{
    auto it = m_nameToModelID.find(name3Dmodel);
    if (it != m_nameToModelID.end())
    {
        return it->second;
    }
    auto path = "assets/models/" + name3Dmodel + ".glb";
    m_models.push_back(LoadModel(path.c_str()));
    size_t id = m_models.size() - 1;
    m_nameToModelID[name3Dmodel] = id;
    return id;
}
Model& AssetManager::GetModel(size_t id) { return m_models[id]; }

std::vector<const game::vehicles::VehicleDefinition*> AssetManager::GetVehicleDatabase() const
{
    std::vector<const game::vehicles::VehicleDefinition*> view;

    for (const auto& [vehicleType, vehicleData] : m_vehicleDatabase)
    {
        view.push_back(vehicleData.get());
    }
    TraceLog(LOG_ERROR, "vracim databazi aut o velikosti: %d", view.size());
    return view;
}

Font AssetManager::GetFont() { return m_font; }
} // namespace game::assets