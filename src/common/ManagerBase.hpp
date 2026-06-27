#pragma once
// just manager base class - with non copyable
#include "NonCopyable.hpp"
namespace game
{
class Manager : public NonCopyable
{
  public:
    Manager() = default;

    virtual void Init() = 0;
    virtual void Shut() {}
};
} // namespace game