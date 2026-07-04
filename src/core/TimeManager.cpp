#include "TimeManager.hpp"
#include "Config.hpp"
#include "TimeContext.hpp"
namespace game
{
void TimeManager::TimeUpdate(float deltaTime)
{
    // normal delta seconds
    m_timeContext.frame = deltaTime;
    // game time delta seconds
    m_timeContext.game = deltaTime * m_gameSpeed * constant::settings::timeRealToGameSeconds;
    // game time minutes
    m_gameSecondsAccumulator += m_timeContext.game;
    while (m_gameSecondsAccumulator > constant::settings::timeRealToGameSeconds)
    {
        m_gameTime.minutes++;
        m_gameSecondsAccumulator -= constant::settings::timeRealToGameSeconds;
    }
}

const TimeContext& TimeManager::GetTimeContext() const { return m_timeContext; }
const GameTime& TimeManager::GetGameTime() const { return m_gameTime; }
bool TimeManager::IsGamePaused() const { return m_gameSpeed == 0; }
} // namespace game