/**
 * @file Config.hpp
 * @author your name (you@domain.com)
 * @brief constants, setting, global stuff
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
namespace game::constant
{
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
namespace settings
{
inline constexpr int winWidth = 1280;
inline constexpr int winHeight = 720;
// size of the map plane
inline constexpr float mapSizeX = 50;
inline constexpr float mapSizeY = 50;
} // namespace settings
} // namespace game::constant