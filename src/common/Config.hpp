/**
 * @file Config.hpp
 * @author komatr
 * @brief constants, setting, default values
 * @date 21.5.2026
 */
#pragma once
namespace game::constant
{
// folders and files paths
namespace path
{
inline constexpr const char* TP = "assets/texturepacks/texturepack.json";
inline constexpr const char* Map = "assets/map.png";
inline constexpr const char* WorldData = "assets/data/world.json";
inline constexpr const char* Font = "assets/fonts/lato_regular.ttf";
inline constexpr const char* VehicleDatabase = "assets/data/vehicles.json";
inline constexpr const char* Models = "assets/models";
inline constexpr const char* FallbackTexture = "assets/fallback_texture.png";
} // namespace path
// default settings
namespace settings
{
// game window
inline constexpr int winWidth = 1280;
inline constexpr int winHeight = 720;
// size of the map plane
inline constexpr float mapSizeX = 50;
inline constexpr float mapSizeY = 50;
// camera Y offset(map - camera distance) is constant = final camera position {x, 25, z}
inline constexpr float camOffsetX = 0.0f;
inline constexpr float camOffsetY = 35.0f;
inline constexpr float camOffsetZ = 18.0f;
inline constexpr float camFov = 25.0f; // flat look (field of view angle) -> map vibe :D
inline constexpr float camZooms[] = {0.5f, 1.0f, 2.0f};
} // namespace settings
} // namespace game::constant