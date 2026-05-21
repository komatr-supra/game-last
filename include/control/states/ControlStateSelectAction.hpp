#pragma once

#include "ControlStateBase.hpp"

struct ControlContext;

class ControlStateSelectAction : public ControlStateBase
{
  private:
    ControlContext& m_context;

  public:
    void OnEnter() override {}
    void Update() override {}
    void OnExit() override {}
};