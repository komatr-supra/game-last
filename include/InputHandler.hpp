#pragma once
#include "Node.hpp"
#include <functional>
#include <memory>
#include <variant>
#include <vector>

#include <map>
class State {
  protected:
    int id;

  public:
    virtual ~State() = default;
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
    const virtual int GetID() const { return id; };
};

struct Transition {
    State *state;
    std::function<bool(void)> condition;
};

State::State() {}

State::~State() {}

class StateMachine {
  private:
    struct Comparator {
        bool operator()(const State *a, const State *b) const { return a->GetID() < b->GetID(); }
    };
    State *m_state;
    std::map<State *, std::vector<Transition>, Comparator> m_transitions;

  public:
    void AddState(State *from, State *to, std::vector<std::function<bool(void)>> changeCondition);
    void SetState(State *state) { m_state = state; }
    StateMachine();
    ~StateMachine();
};

inline void StateMachine::AddState(State *from, State *to,
                                   std::vector<std::function<bool(void)>> changeCondition) {
    auto it = m_transitions.find(from);
}

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {}

class Car;
using WorldObject = std::variant<std::monostate, Node *, Road *, Car *>;

class InputHandler {
  private:
    WorldObject selected = std::monostate{};
    WorldObject hovered = std::monostate{};

  public:
    InputHandler(/* args */);
    ~InputHandler();
    void Update();
    bool Hover(Vector2 worldPos);
    WorldObject Select();
};

InputHandler::InputHandler(/* args */) {}

InputHandler::~InputHandler() {}

void InputHandler::Update() {}
