/**
 * @file AssetManager.cpp
 * @author komatr
 * @date 18.06.2026
 */
#include "AssetManager.hpp"

#include "Config.hpp"
#include "json.hpp"
#include "raylib.h"
#include "vehicles/VehicleDefinition.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace pth = game::constant::path;
namespace dset = game::constant::settings;
namespace fs = std::filesystem;
namespace veh = game::vehicles;

namespace game::core
{
void AssetManager::Init()
{
    // FALLBACK ASSETS
    TraceLog(LOG_INFO, "Loading fallback assets...");
    Texture2D texture = LoadTexture(pth::FallbackTexture);
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
    Mesh terrainMesh = GenMeshPlane(dset::mapSizeX, dset::mapSizeY, 1, 1);
    m_models.push_back(LoadModelFromMesh(terrainMesh));
    size_t mapModelID = m_models.size() - 1;
    m_nameToModelID["map"] = mapModelID;
    auto map = LoadTexture(pth::Map);
    m_textures["map"] = map;
    SetTextureFilter(map, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(map, TEXTURE_WRAP_CLAMP);
    m_models[mapModelID].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = map;
    if (IsTextureValid(map) && IsModelValid(m_models[mapModelID]))
    {

        TraceLog(LOG_INFO, "SUCCESS");
        TraceLog(LOG_INFO, "texture size: %d, %d", map.width, map.height);
    }
    else throw std::runtime_error("Map Plane loading FAILED!");

    // FONT
    TraceLog(LOG_INFO, "Loading font...");
    m_font = LoadFontEx(pth::Font, 32, nullptr, 0);
    SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
    if (IsFontValid(m_font)) TraceLog(LOG_INFO, "Font loading ... SUCCESS");
    else
    {
        TraceLog(LOG_ERROR, "Font loading FAILED");
        TraceLog(LOG_WARNING, "Using default font");
        m_font = GetFontDefault();
    }

    // TEXTUREPACK
    TraceLog(LOG_INFO, "Loading Textures...");
    TraceLog(LOG_INFO, "Opening texture json file: %s", pth::TP);
    std::ifstream f_tp(pth::TP);
    if (!f_tp.is_open()) { throw std::runtime_error("Texturepack file open FAILED!"); }
    TraceLog(LOG_INFO, "Parsing json file...");
    nlohmann::json data = nlohmann::json::parse(f_tp, nullptr, false);
    TraceLog(LOG_INFO, "Closing json file");
    f_tp.close();
    if (data.is_discarded()) { throw std::runtime_error("Json file for texturepack can't be parsed - file exist, but can't read."); }

    // TEXTURES
    std::vector<Texture2D*> texturesByID; // relative indexed textures - for sprite parse
    for (size_t i = 0; i < data["textures"].size(); i++)
    {
        fs::path path = pth::TP;
        fs::path textureName = data["textures"][i].get<std::string>();
        path = path.remove_filename() / textureName;
        TraceLog(LOG_INFO, "texture path is: %s", (path).c_str());
        auto tex = LoadTexture(path.c_str());
        if (!IsTextureValid(tex)) { TraceLog(LOG_ERROR, "Loading texture: %s ... !!!FAILED!!!", path.c_str()); }
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
            if (spriteNP.nPatchInfo.right == 0 && spriteNP.nPatchInfo.left == 0) spriteNP.nPatchInfo.layout = NPATCH_THREE_PATCH_VERTICAL;
            else if (spriteNP.nPatchInfo.top == 0 && spriteNP.nPatchInfo.bottom == 0)
                spriteNP.nPatchInfo.layout = NPATCH_THREE_PATCH_HORIZONTAL;
            else spriteNP.nPatchInfo.layout = NPATCH_NINE_PATCH;

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
    // TODO: create DataLoader -> move loading staff inside (from this FILE)
    // VEHICLES
    std::ifstream f_vd(pth::VehicleDatabase);
    if (!f_vd.is_open()) { throw std::runtime_error("Vehicle Databese data file open FAILED!"); }
    nlohmann::json dataVehiclesJSON = nlohmann::json::parse(f_vd);
    f_vd.close();
    if (dataVehiclesJSON.is_discarded()) { throw std::runtime_error("Json file for texturepack is broken."); }
    int generatedID = 1;
    for (auto& vehicleJSON : dataVehiclesJSON["vehicles"])
    {
        veh::CarType carType = GetCarType(vehicleJSON["type"].get<std::string>());
        m_vehicleDatabase.push_back(
            std::make_unique<veh::VehicleDefinition>(generatedID++,
                                                     vehicleJSON["name"].get<std::string>(),
                                                     carType,
                                                     vehicleJSON["maxSpeed"].get<int>(),
                                                     vehicleJSON["maxCapacity"].get<int>(),
                                                     vehicleJSON["price"].get<int>(),
                                                     GetSprite(vehicleJSON["resource"].get<std::string>()),
                                                     GetOrCreateModelID(vehicleJSON["resource"].get<std::string>())));
        TraceLog(LOG_INFO, "Vehicle \"%s\" in database CREATED", vehicleJSON["name"].get<std::string>().c_str());
    }
    // CITIES
    GetOrCreateModelID("building"); // TEST
}

void AssetManager::Shut()
{
    // unload ALL
    UnloadFont(m_font);
    for (auto& [name, texture] : m_textures) UnloadTexture(texture);
    for (auto& model : m_models) UnloadModel(model);
}
const Texture2D& AssetManager::GetTexture(const std::string& textureName) const
{
    auto it = m_textures.find(textureName);
    if (it != m_textures.end()) { return it->second; }

    return m_textures.at(fallback);
}
const Sprite& AssetManager::GetSprite(const std::string& spriteName) const
{
    auto it = m_sprites.find(spriteName);
    if (it != m_sprites.end()) { return it->second; }

    return m_sprites.at(fallback);
}

const SpriteNP& AssetManager::GetSpriteNP(const std::string& spriteName) const
{
    auto it = m_spritesNP.find(spriteName);
    if (it != m_spritesNP.end()) { return it->second; }
    return m_spritesNP.at(fallback);
}
size_t AssetManager::GetOrCreateModelID(const std::string& modelName)
{
    auto it = m_nameToModelID.find(modelName);
    if (it != m_nameToModelID.end()) { return it->second; }
    auto path = "assets/models/" + modelName + ".glb";
    auto model = LoadModel(path.c_str());
    for (int i = 0; i < model.materialCount; i++)
    {
        // 1. Každému materiálu vnutí kód náš lighting shader
        // model.materials[i].shader = lightingShader;

        model.materials[i].maps[MATERIAL_MAP_DIFFUSE].value = 1;
    }
    m_models.push_back(model);
    size_t id = m_models.size() - 1;
    m_nameToModelID[modelName] = id;
    return id;
}

const Model& AssetManager::GetModel(size_t id) const { return m_models[id]; }

const Model& AssetManager::GetModel(const std::string& modelName) const
{
    auto it = m_nameToModelID.find(modelName);
    if (it != m_nameToModelID.end()) { return GetModel(it->second); }
    return GetModel(0);
}

std::vector<const game::vehicles::VehicleDefinition*> AssetManager::GetVehicleDatabase() const
{

    std::vector<const veh::VehicleDefinition*> view;

    for (const auto& vehicleData : m_vehicleDatabase) { view.push_back(vehicleData.get()); }
    // TraceLog(LOG_ERROR, "vracim databazi aut o velikosti: %d, celkova velikost databaze je: %d", view.size(), m_vehicleDatabase.size());
    return view;
}

const Font& AssetManager::GetFont() const { return m_font; }

veh::CarType AssetManager::GetCarType(const std::string& carName) const
{
    auto it = conversionMap.find(carName);
    if (it != conversionMap.end()) { return it->second; }

    return veh::CarType::NOT_SET;
}
const std::string& AssetManager::GetTypeText(game::vehicles::CarType type) const
{
    for (auto [carName, enumValue] : conversionMap)
    {
        if (enumValue == type) return carName;
    }

    return fallback;
}

const veh::VehicleDefinition& AssetManager::GetVehicleDefinition(int carID)
{
    auto it = std::find_if(m_vehicleDatabase.begin(),
                           m_vehicleDatabase.end(),
                           [carID](const std::unique_ptr<game::vehicles::VehicleDefinition>& vehicle) { return vehicle->id == carID; });
    if (it != m_vehicleDatabase.end()) return *it->get();
    return *m_vehicleDatabase[0];
}
} // namespace game::core