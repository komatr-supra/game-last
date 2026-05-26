#pragma once

#include "control/gui/GuiDashboard.hpp"
#include "core/AssetManager.hpp"

class GuiManager
{
  private:
    GuiDashboard m_dashboard;
    VehicleManager& m_vehicleManager;

  public:
    GuiManager(AssetManager& am, VehicleManager& vm);
    ~GuiManager();

    void Draw();
};

GuiManager::GuiManager(AssetManager& am, VehicleManager& vm) : m_dashboard(am, vm), m_vehicleManager(vm) {}

GuiManager::~GuiManager() {}

void GuiManager::Draw() { m_dashboard.Draw(); }
