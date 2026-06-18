/**
 * @file TimeManager.hpp
 * @author komatr
 * @brief game time handler - fime stop, multiply, convert real time <-> game time, and handle callbacks based on game
 * time
 * @date 16.6.2026
 */
#pragma once
namespace game::core
{

class TimeManager
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
} // namespace game::core