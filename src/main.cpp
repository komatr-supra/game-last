#include "Config.hpp"

#include "raylib.h"

int main(void)
{
    InitWindow(1280, 720, "Raylib");
    SetTargetFPS(60);

    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();
        // BeginMode2D(cameraController.GetCamera());
        ClearBackground(RAYWHITE);
        // map.Draw();
        // vehicleManager.DrawAllVehicles();
        // EndMode2D();
        // guiManager.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}