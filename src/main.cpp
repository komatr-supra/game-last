#include "AssetManager.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Map.hpp"
#include "raylib.h"

int main(void)
{
    InitWindow(game::constant::settings::winWidth, game::constant::settings::winHeight, "STD");
    SetTargetFPS(60);

    game::camera::GameCamera cam;

    game::assets::AssetManager am;

    game::world::Map map(am);
    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {

        cam.Update(GetTime());
        BeginDrawing();
        ClearBackground(GRAY);
        // 3D objects - map, vehicles
        BeginMode3D(cam.GetCam());
        map.Draw();
        EndMode3D();
        // GUI
        EndDrawing();
    }

    CloseWindow();

    return 0;
}