#pragma once
#include "TimeContext.hpp"
namespace game
{

class IUpdateable
{
  public:
    virtual ~IUpdateable() = default;
    virtual void Update(TimeContext time) = 0;
};
} // namespace game