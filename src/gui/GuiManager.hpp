#pragma once
#include "Core.hpp"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "vehicles/Vehicle.hpp"
#include "vehicles/VehicleDefinition.hpp"
#include "vehicles/VehicleManager.hpp"

// test
#include <cstdlib>
#include <ctime>
#include <imgui_internal.h>
#include <string>

namespace game::gui
{
class GuiManager : public game::core::Manager
{
  private:
    game::vehicles::VehicleManager& vm;

  public:
    GuiManager(game::vehicles::VehicleManager& vehicleManager) : vm(vehicleManager) { std::srand(std::time(nullptr)); }
    void Draw();
    void Init() override;
};
inline void GuiManager::Draw()
{
    rlImGuiBegin();

    // 1. Spočítáme rozměry pro pravý sloupec (1/4 obrazovky)
    float screenWidth = ImGui::GetMainViewport()->Size.x;
    float screenHeight = ImGui::GetMainViewport()->Size.y;
    float panelWidth = screenWidth * 0.25f;
    float startX = screenWidth - panelWidth;

    // Rozdělíme výšku obrazovky rovnoměrně mezi 4 okna
    float windowHeight = screenHeight / 4.0f;

    // 2. Vykreslení samostatných oken (ImGuiCond_FirstUseEver zajistí,
    // že pozice se nastaví jen poprvé, pak už si to řídí hráč sám)

    // --- 1. OKNO: FLEET ---
    ImGui::SetNextWindowPos(ImVec2(startX, windowHeight * 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, windowHeight), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Fleet"))
    {
        for (auto* vehicle : vm.GetVehicles())
        {
            ImGui::PushID(vehicle);
            if (ImGui::CollapsingHeader(vehicle->GetName().c_str()))
            {
                ImGui::Text("informace o aute a hodne dlouhy text, jak bude zalamovani fungovat, tho rozbalovani ma neco do sebe");
            }

            ImGui::PopID();
            ImGui::Separator();
        }
    }
    ImGui::End();

    // --- 2. OKNO: ACTIVE JOBS ---
    ImGui::SetNextWindowPos(ImVec2(startX, windowHeight * 1), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, windowHeight), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Active jobs")) { ImGui::Text("Rozdělaná práce..."); }
    ImGui::End();

    // --- 3. OKNO: MARKET ---
    ImGui::SetNextWindowPos(ImVec2(startX, windowHeight * 2), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, windowHeight), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Market")) { ImGui::Text("Tržiště zakázek..."); }
    ImGui::End();

    // --- 4. OKNO: SHOP ---
    ImGui::SetNextWindowPos(ImVec2(startX, windowHeight * 3), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, windowHeight), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Shop"))
    {
        for (const auto* vehicle : vm.GetVehicleDatabase())
        {
            if (vehicle->type == vehicles::CarType::NOT_SET) continue;
            ImGui::PushID(vehicle);
            // 1. line
            ImGui::Text("%s", vehicle->name.c_str());
            ImGui::SameLine();
            ImGui::Text("(type: %s)", vm.GetVehicleTypeText(vehicle->type).c_str());
            // 2. line
            ImGui::Text("Capacity: %d units", vehicle->capacityMax);
            ImGui::SameLine(0, 20.0f);
            std::string capacityVisual = "";
            for (int i = 0; i < vehicle->capacityMax; i++) { capacityVisual += "●"; }
            ImGui::Text("%s", capacityVisual.c_str());
            // 3. line
            ImGui::Text("Speed: %d km/h", vehicle->speedMax);
            ImGui::SameLine(0, 20.0f);
            ImGui::ProgressBar(vehicle->speedMax / 190.f, ImVec2(ImGui::GetContentRegionAvail().x, 20.0f), "");
            // 4.line
            ImGui::Text("Cost: %d$", vehicle->price);
            ImGui::SameLine(.0f, 10.0f);
            float restWidth = ImGui::GetContentRegionAvail().x;
            if (ImGui::Button("BUY", ImVec2(restWidth, 30))) { vm.CreateVehicle(vehicle->id, std::rand() % 7); }
            ImGui::PopID();
            ImGui::Separator();
        }
    }
    ImGui::End();

    rlImGuiEnd();
}

inline void GuiManager::Init()
{
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    ImFontConfig fontConfig;
    fontConfig.GlyphExtraAdvanceX = 1.0f;
    fontConfig.PixelSnapH = true;
    fontConfig.OversampleH = 3;
    fontConfig.OversampleV = 2;
    auto fnt = io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 20.0f, &fontConfig);
    io.FontDefault = fnt;
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg].w = 0.80f;
    style.Colors[ImGuiCol_TitleBgActive].w = 0.85f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.8, 0.8, 1.0f);
}
} // namespace game::gui