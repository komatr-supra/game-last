#pragma once
namespace game
{
// non copyable class to avoid duplication
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

} // namespace game