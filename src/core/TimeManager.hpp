/**
 * @file TimeManager.hpp
 * @author komatr
 * @brief game time clock, tick provider, can register callback... TODO: think about it
 * @date 16.6.2026
 */
#pragma once
#include "ManagerBase.hpp"
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
    explicit Time(int gameMinutes = 0) : minutes(gameMinutes) {}
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

class TimeManager : public Manager
{
  private:
    bool m_isGamePaused = false;
    int m_gameSpeed = 1;
    int m_totalSeconds = 0;
    float m_fractionSecond = 0;
    int m_gameMinutes = 0;
    float m_deltaTime = 0;

  public:
    void Update(float deltaTime)
    {
        m_deltaTime = deltaTime;
        if (m_isGamePaused) return;

        m_fractionSecond += m_deltaTime;
        if (m_deltaTime >= 1.0f)
        {
            m_totalSeconds++;
            m_gameMinutes += m_gameSpeed;
            m_fractionSecond -= 1.0f;
        }
    }

    int GetGameTime() { return m_gameMinutes; }
    int GetDeltaTime() { return m_deltaTime; }
};
} // namespace game