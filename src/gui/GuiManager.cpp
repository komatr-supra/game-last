#include "GuiManager.hpp"
#include "imgui.h"
#include "rlImGui.h"
#include "vehicles/VehicleManager.hpp"

namespace game::gui
{

void GuiManager::Draw()
{
    rlImGuiBegin();

    // 1. window - fleet
    if (ImGui::Begin("Fleet")) { m_fleetWindiow.Draw(); }
    ImGui::End();
    // --- 2. OKNO: ACTIVE JOBS ---
    if (ImGui::Begin("Active jobs")) { ImGui::Text("Rozdělaná práce..."); }
    ImGui::End();

    // --- 3. OKNO: MARKET ---
    if (ImGui::Begin("Market")) { ImGui::Text("Tržiště zakázek..."); }
    ImGui::End();

    // --- 4. OKNO: SHOP ---
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
    // ImGui::PopStyleVar();
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
    auto fnt = io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 24.0f, &fontConfig);
    io.FontDefault = fnt;
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 5.0f;
    style.ChildRounding = 5.0f;
    style.FrameRounding = 5.0f;
    style.Colors[ImGuiCol_WindowBg].w = 0.85f;
    style.Colors[ImGuiCol_TitleBgActive].w = 0.9f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.8, 0.8, 1.0f);
    ImVec4 col_normal = ImVec4(0.12f, 0.20f, 0.40f, 1.0f);
    ImVec4 col_hover = ImVec4(0.20f, 0.35f, 0.60f, 1.0f);
    ImVec4 col_active = ImVec4(0.2f, 0.60f, 0.2f, 1.0f);
    style.Colors[ImGuiCol_Button] = col_normal;
    style.Colors[ImGuiCol_ButtonActive] = col_active;
    style.Colors[ImGuiCol_ButtonHovered] = col_hover;
}
} // namespace game::gui