#include "CameraController.hpp"
#include "Fleet.hpp"
#include "Renderer.hpp"
#include "World.hpp"
#include "raylib.h"
#define MAP_ROLL_SPD 5

int main(void) {
    // 1. Inicializace (vypneme otravné logy, aby zářilo naše LOG_INFO)
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(1280, 720, "Raylib");
    SetTargetFPS(60);

        World world;
    Renderer rend(world);
    Fleet fleet;
    auto c = fleet.CreateCar(world.Cities[0].get());
    CameraController cameraController = {
        GetScreenWidth(),
        GetScreenHeight(),
        {static_cast<float>(mapTexture.width), static_cast<float>(mapTexture.height)}};

    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        Vector2 mouseWorldPos = GetScreenToWorld2D(mousePos, cameraController.GetCamera());

        world.Hover(mouseWorldPos);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            auto obj = world.Select();
            if (std::holds_alternative<Node *>(obj)) {
                auto cityStart = c->Path.empty() ? c->city : c->Path.back().city;
                auto cityEnd = std::get<Node *>(obj);
                auto p = world.GetRoadBetweenCities(cityStart, cityEnd);
                if (p)
                    c->AddPointToPath(cityEnd, p);
            }
        }
        Vector2 moveCameraVector = {static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
                                    static_cast<float>(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))};
        cameraController.MoveCamera(Vector2Scale(moveCameraVector, MAP_ROLL_SPD));

        fleet.Update(0.05f);

        BeginDrawing();
        BeginMode2D(cameraController.GetCamera());
        ClearBackground(RAYWHITE);
        DrawTexture(mapTexture, 0, 0, WHITE);
        rend.Draw();
        fleet.Draw();
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}