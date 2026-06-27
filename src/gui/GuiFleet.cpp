#include "GuiFleet.hpp"
#include "graphics/GameCamera.hpp"
#include "imgui.h"
#include "raylib.h"
#include "vehicles/Vehicle.hpp"
#include "vehicles/VehicleManager.hpp"
#include <cfloat>

using namespace ImGui;

namespace game::gui
{
GuiFleet::GuiFleet(game::vehicles::VehicleManager& vehicleManager, game::graphics::GameCamera& camera)
    : m_vehicleManager(vehicleManager), m_cam(camera)
{
}
void GuiFleet::Draw()
{

    //  draw all cars
    // 3 lines per vehicle
    // 1. button center camera at this vehicle + vehicle name + button vehicle settings(info)
    // 2. cargo capacity in format: [capacity/carry icon] 0/6 (used cargo slots/max capacity) oooooo (outline circle for free slots,
    // filled circle for used slots)
    // 3. button to open shedule window for this vehicle, TEXT an the button is current action + progress: "Driving PRG-MUN (31%)"
    for (auto* vehicle : m_vehicleManager.GetVehicles())
    {
        Dummy(ImVec2(0, 10.0f));
        PushID(vehicle);
        BeginGroup();
        Text("%s", vehicle->GetName().c_str());
        SameLine();
        ImVec2 iconSize = ImGui::CalcTextSize("Show");
        float btnSize = (iconSize.x + ImGui::GetStyle().FramePadding.x * 3) * 2; // Výpočet velikosti
        float space = GetContentRegionAvail().x - btnSize - ImGui::GetStyle().FramePadding.x;
        Dummy(ImVec2(space, 0));
        SameLine();
        if (Button("show")) { TraceLog(LOG_INFO, "focus camera on this vehicle"); }
        // m_cam.Follow(&vehicle->GetPosition());
        SameLine();
        if (Button("info")) { TraceLog(LOG_INFO, "open settings for this vahicle"); }
        Text("o o o o o o o");
        SameLine();
        // todo real speed
        const char* speedText = "100km/h";
        ImVec2 speedTextSize = CalcTextSize(speedText);
        space = GetContentRegionAvail().x - speedTextSize.x;
        Dummy(ImVec2(space, 0));
        Text("%s", speedText);
        // todo import action data
        if (Button("current action data", ImVec2(-FLT_MIN, 0)))
        {
            // todo open a new window, graphicaly connect(color)
            TraceLog(LOG_INFO, "open schedule");
        }
        EndGroup();
        PopID();
        Dummy(ImVec2(0, 10.0f));
        Separator();
    }
}
} // namespace game::gui