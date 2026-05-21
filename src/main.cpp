#include "core/AssetManager.hpp"
#include "core/Camera.hpp"
#include "core/Map.hpp"
#include "vehicle/VehicleManager.hpp"

#include "raylib.h"

#define MAP_ROLL_SPD 5

int main(void)
{
    // 1. Inicializace (vypneme otravné logy, aby zářilo naše LOG_INFO)
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(1280, 720, "Raylib");
    SetTargetFPS(60);

    AssetManager assetManager;
    Map map{assetManager};
    VehicleManager vehicleManager{assetManager};
    // auto c = vehicleManager.CreateCar(world.m_cities[0].get());
    CameraController cameraController = {GetScreenWidth(), GetScreenHeight(), map.GetMapSize()};

    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        Vector2 mouseWorldPos = GetScreenToWorld2D(mousePos, cameraController.GetCamera());

        Vector2 moveCameraVector = {static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
                                    static_cast<float>(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))};
        cameraController.MoveCamera(Vector2Scale(moveCameraVector, MAP_ROLL_SPD));

        vehicleManager.Update(0.05f);

        BeginDrawing();
        BeginMode2D(cameraController.GetCamera());
        ClearBackground(RAYWHITE);
        map.Draw();
        // vehicleManager.Draw();
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}