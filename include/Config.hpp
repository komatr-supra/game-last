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
#include "texturepack.hpp"
namespace game::constant
{
namespace path
{
inline constexpr const char* TP = "assets/texturepacks/";
inline constexpr const char* MapTexture = "assets/map.png";
inline constexpr const char* WorldData = "assets/data/world.json";
inline constexpr const char* Font = "assets/fonts/lato_regular.ttf";
inline constexpr const char* VehicleDatabase = "assets/data/vehicles.json";
} // namespace path
namespace settings
{
inline constexpr int winWidth = 1280;
inline constexpr int winHeight = 720;

} // namespace settings
} // namespace game::constant