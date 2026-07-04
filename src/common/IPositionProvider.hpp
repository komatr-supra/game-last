#pragma once
struct Vector3;
namespace game
{

class IPositionProvider
{
  public:
    virtual ~IPositionProvider() = default;
    virtual const Vector3& GetPosition() const = 0;
};
} // namespace game