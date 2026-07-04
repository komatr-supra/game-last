/**
 * @file TimeManager.hpp
 * @author komatr
 * @brief game time clock, tick provider, can register callback... TODO: think about it
 * @date 16.6.2026
 */
#pragma once
#include "ManagerBase.hpp"
#include "TimeContext.hpp"
#include <compare>

namespace game
{
struct GameTime
{
    int minutes;
    int ToHours() { return minutes / 60; }
    int ToDays() { return minutes / 60 / 24; }
    int ToMonths() { return minutes / 60 / 24 / 30; }
    int ToYears() { return minutes / 60 / 24 / 30 / 12; }
    explicit GameTime(int gameMinutes = 0) : minutes(gameMinutes) {}
    GameTime& operator+=(const GameTime& b)
    {
        this->minutes += b.minutes;
        return *this;
    }
    GameTime& operator-=(const GameTime& b)
    {
        this->minutes -= b.minutes;
        return *this;
    }
    GameTime operator+(const GameTime& b) const { return GameTime(minutes + b.minutes); }
    GameTime operator-(const GameTime& b) const { return GameTime(minutes - b.minutes); }
    GameTime& operator++()
    {
        minutes++;
        return *this;
    }
    GameTime& operator--()
    {
        minutes--;
        return *this;
    }
    auto operator<=>(const GameTime&) const = default;
};

class TimeManager : public Manager
{
  private:
    int m_gameSpeed = 1;
    float m_gameSecondsAccumulator = 0;
    GameTime m_gameTime{0};
    TimeContext m_timeContext{0, 0};

  public:
    void TimeUpdate(float deltaTime);
    const TimeContext& GetTimeContext() const;
    const GameTime& GetGameTime() const;
    bool IsGamePaused() const;
};
} // namespace game