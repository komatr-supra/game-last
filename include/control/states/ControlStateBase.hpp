#pragma once

class ControlStateBase
{
  public:
    virtual ~ControlStateBase() = default;
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
};