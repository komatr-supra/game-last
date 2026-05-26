#pragma once

#include "control/gui/GuiDashboard.hpp"
#include "core/AssetManager.hpp"

class GuiManager
{
  private:
    GuiDashboard m_dashboard;

  public:
    GuiManager(AssetManager& am);
    ~GuiManager();

    void Draw();
};

GuiManager::GuiManager(AssetManager& am) : m_dashboard(am) {}

GuiManager::~GuiManager() {}

void GuiManager::Draw() { m_dashboard.Draw(); }
