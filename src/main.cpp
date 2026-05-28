#include "Config.hpp"

#include "core/AssetManager.hpp"
#include "core/Camera.hpp"
#include "core/Map.hpp"
#include "vehicle/VehicleManager.hpp"

#include "raylib.h"

#include "control/gui/GuiManager.hpp"

#include "vehicle/Vehicle.hpp"
#include "vehicle/tasks/VehicleTaskBase.hpp"
#include "vehicle/tasks/VehicleTaskMoving.hpp"

int main(void)
{
    // 1. Inicializace (vypneme otravné logy, aby zářilo naše LOG_INFO)
    SetTraceLogLevel(LOG_INFO);
    InitWindow(1280, 720, "Raylib");
    SetTargetFPS(60);

    AssetManager assetManager;
    Map map{assetManager};
    VehicleManager vehicleManager{assetManager};
    // auto c = vehicleManager.CreateCar(world.m_cities[0].get());
    CameraController cameraController = {GetScreenWidth(), GetScreenHeight(), map.GetMapSize()};
    GuiManager guiManager{assetManager, vehicleManager};
    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        Vector2 mouseWorldPos = GetScreenToWorld2D(mousePos, cameraController.GetCamera());

        Vector2 moveCameraVector = {static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
                                    static_cast<float>(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))};
        cameraController.MoveCamera(Vector2Scale(moveCameraVector, 8));

        vehicleManager.Update(0.05f);
        if (IsKeyPressed(KEY_H))
        {
            auto city1 = map.GetCityByID(1);
            auto car = vehicleManager.CreateVehicle(city1, "Dodge");
            auto city2 = map.GetCityByID(1);
            auto pathh = map.GetRoadBetweenCities(city1, city2);
            car->AddTask(std::make_unique<VehicleTaskMoving>(pathh, *car, "jizda auta"));
        }
        BeginDrawing();
        BeginMode2D(cameraController.GetCamera());
        ClearBackground(RAYWHITE);
        map.Draw();
        vehicleManager.DrawAllVehicles();
        EndMode2D();
        guiManager.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}