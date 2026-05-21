/**
 * @file ControlStateBase.hpp
 * @author your name (you@domain.com)
 * @brief main class for control (also user input)
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

class ControlStateBase
{
  public:
    virtual ~ControlStateBase() = default;
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
};