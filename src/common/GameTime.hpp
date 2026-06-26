/**
 * @file GameTime.hpp
 * @author komatr
 * @brief game time data
 * @date 18.06.2026
 */
#pragma once

#include <compare>

namespace game
{
struct Time
{
    int minutes;
    int ToHours() { return minutes / 60; }
    int ToDays() { return minutes / 60 / 24; }
    int ToMonths() { return minutes / 60 / 24 / 30; }
    int ToYears() { return minutes / 60 / 24 / 30 / 12; }
    Time(int time) : minutes(time = 0) {}
    Time& operator+=(const Time& b)
    {
        this->minutes += b.minutes;
        return *this;
    }
    Time& operator-=(const Time& b)
    {
        this->minutes -= b.minutes;
        return *this;
    }
    Time operator+(const Time& b) const { return Time(minutes + b.minutes); }
    Time operator-(const Time& b) const { return Time(minutes - b.minutes); }
    Time& operator++()
    {
        minutes++;
        return *this;
    }
    Time& operator--()
    {
        minutes--;
        return *this;
    }
    auto operator<=>(const Time&) const = default;
};

} // namespace game