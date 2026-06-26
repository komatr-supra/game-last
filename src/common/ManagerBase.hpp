#pragma once
namespace game
{
class NonCopyable
{
  protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

  public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};

class Manager : public NonCopyable
{
  public:
    Manager() = default;
    virtual ~Manager() = default;

    virtual void Init() = 0;
    virtual void Shut() {}
};
} // namespace game