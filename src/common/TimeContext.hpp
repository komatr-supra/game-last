// just frame delta Time and game Time(delta with multiplier "0" for pause) floats together
#pragma once

namespace game
{
struct TimeContext
{
    float frame;
    float game;
};
} // namespace game