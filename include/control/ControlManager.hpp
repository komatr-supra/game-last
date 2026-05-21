#pragma once

#include <memory>
#include <variant>
#include <vector>

struct ControlStateBase;

class Controller
{
  private:
    enum class CONTROL_STATE
    {
        ACTION_SELECT,
        SCHEDULE_CREATING
    };
    std::vector<ControlStateBase*> m_states;
    /* data */
  public:
    Controller(/* args */);
    ~Controller();
};

Controller::Controller(/* args */) {}

Controller::~Controller() {}
