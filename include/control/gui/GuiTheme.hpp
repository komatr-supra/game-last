#pragma once

#include "raylib.h"

namespace game::gui
{
inline constexpr const char* ResourcePath = "" namespace colors
{

    inline constexpr Color MainBg = {0x0B, 0x0F, 0x19, 0xF8};
    inline constexpr Color MainBorder = {0x00, 0xE5, 0xFF, 0xFF};
    inline constexpr Color Shadow = {0x00, 0x00, 0x00, 0x70};

    inline constexpr Color ContentBg = {0x17, 0x1E, 0x30, 0xFF};
    inline constexpr Color ContentBorder = {0x2D, 0x3B, 0x5E, 0xFF};

    inline constexpr Color BtnNormal = {0x25, 0x35, 0x56, 0xFF};
    inline constexpr Color BtnHover = {0x38, 0xBD, 0xF8, 0xFF};
    inline constexpr Color BtnClick = {0x1E, 0x2D, 0x4A, 0xFF};

    inline constexpr Color TextMain = {0xF8, 0xFA, 0xFC, 0xFF};
    inline constexpr Color TextMuted = {0x64, 0x74, 0x8B, 0xFF};

    inline constexpr Color Disable = {0x47, 0x55, 0x69, 0xFF};
    inline constexpr Color Success = {0x00, 0xF5, 0xB4, 0xFF};
    inline constexpr Color Alert = {0xFF, 0x6B, 0x6B, 0xFF};
    inline constexpr Color Profit = {0xFF, 0x9F, 0x1C, 0xFF};

} // namespace colors
namespace sprites
{
inline constexpr const char* Background = "background";
inline constexpr const char* Border = "border";
inline constexpr const char* LineH = "lineH";
inline constexpr const char* LineV = "lineV";
inline constexpr const char* Vehicles = "vehicles";
inline constexpr const char* Manifests = "manifests";
inline constexpr const char* Marketplace = "marketplace";
inline constexpr const char* Sabotages = "sabotages";
} // namespace sprites
} // namespace game::gui