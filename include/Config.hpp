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

namespace Config
{
namespace FilePaths
{
inline constexpr const char* Vehicles = "data/vehicles.json";
inline constexpr const char* TexturePack = "data/texture_pack.json";
inline constexpr const char* MapData = "data/map.json";
inline constexpr const char* Font = "data/Lato-Regular.ttf";
} // namespace FilePaths
namespace Control
{
inline float MapRollSpeed = 8;
}
namespace ImageNames
{
}
} // namespace Config