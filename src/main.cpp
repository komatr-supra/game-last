#include "Config.hpp"
#include "Sprite.hpp"
#include "core/AssetManager.hpp"
#include "raylib.h"
#include "core/Camera.hpp"

int main(void)
{
    InitWindow(game::constant::settings::winWidth, game::constant::settings::winHeight, "STD");
    SetTargetFPS(60);

    
    game::core::GameCamera cam;
    AssetManager am;
    Sprite test = am.GetSprite(game::constant::sprite::s_gui_icon_calendar);

    Mesh testPlane = GenMeshPlane(40, 40, 1, 1);
    Model testModel = LoadModelFromMesh(testPlane);
    testModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = am.GetMapTexture();
    // --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {
        
        cam.Update({0, 0}, GetTime());
        BeginDrawing();
        ClearBackground(GRAY);
        BeginMode3D(cam.GetCam());
        DrawModel(testModel, {0,0,0}, 1, WHITE);
        EndMode3D();
        DrawSprite(test, {500, 500});
        EndDrawing();
    }

    CloseWindow();

    return 0;
}