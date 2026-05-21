/**
 * @file ControlStateSelectAction.hpp
 * @author your name (you@domain.com)
 * @brief starting action, something like IDLE
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
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