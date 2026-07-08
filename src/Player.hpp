#pragma once
#include "IPositionProvider.hpp"
#include "IUpdateable.hpp"
#include "Id.hpp"
#include "TimeContext.hpp"
#include "camera/CameraPlayerAnchor.hpp"
namespace game::player
{
struct PlayerID
{
};
class Player : public IUpdateable
{
  private:
    TypeID<PlayerID> m_id;
    game::camera::CameraPlayerAnchor m_cameraAnchor;
    IPositionProvider* m_followedObject;

  public:
    const IPositionProvider* GetTrackedPositionProvider() const { return m_followedObject; }
    const TypeID<PlayerID>& GetPlayerId() const { return m_id; }

    void Update(TimeContext time) override { return; }
};
} // namespace game::player