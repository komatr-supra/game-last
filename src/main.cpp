#include "AssetManager.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Map.hpp"
#include "raylib.h"
#include "raymath.h"
#include "vehicle/Vehicle.hpp"
#include "vehicle/VehicleManager.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

int main(void)
{
    InitWindow(game::constant::settings::winWidth, game::constant::settings::winHeight, "STD");
    SetTargetFPS(120);

    game::camera::GameCamera cam;
    game::assets::AssetManager am;
    game::world::Map map(am);
    game::vehicles::VehicleManager vm(am);
    Vector3 point;
    Model modelTest = LoadModel("assets/models/sedan.glb");
    Shader lightingShader = LoadShader(TextFormat("assets/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                                       TextFormat("assets/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightingShader, "viewPos");
    int ambientLoc = GetShaderLocation(lightingShader, "ambient");
    float ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    SetShaderValue(lightingShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    Light light = CreateLight(LIGHT_DIRECTIONAL, {-10, 30, 20}, Vector3Zero(), GRAY, lightingShader);
    for (int i = 0; i < modelTest.materialCount; i++)
    {
        // 1. Každému materiálu vnutí kód náš lighting shader
        modelTest.materials[i].shader = lightingShader;

        // 2. Zapne texturu pro daný materiál (tohle opraví to GLB)
        modelTest.materials[i].maps[MATERIAL_MAP_DIFFUSE].value = 1;
    }
    auto car = vm.CreateVehicle(game::vehicles::CarType::Pickup);
    TraceLog(LOG_WARNING, "auto se jmenuje: %s", car->GetName().c_str());
    //      --- HLAVNÍ SMYČKA ---
    while (!WindowShouldClose())
    {
        float camPos[3] = {cam.GetCam().position.x, cam.GetCam().position.y, cam.GetCam().position.z};
        SetShaderValue(lightingShader, lightingShader.locs[SHADER_LOC_VECTOR_VIEW], camPos, SHADER_UNIFORM_VEC3);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && map.TryGetRaycast(cam.GetCam(), point))
        {
            cam.Follow(&point);
            TraceLog(LOG_WARNING, "new follow point for camera is set");
        }

        BeginDrawing();
        ClearBackground(GRAY);
        // 3D objects - map, vehicles
        BeginMode3D(cam.GetCam());
        map.Draw();
        // BeginShaderMode(lightingShader);
        DrawCube({0, 0, 0}, 1, 1, 1, WHITE);
        DrawModelEx(modelTest, {0, 1, 0}, {0, 1, 0}, 45, {1, 1, 1}, WHITE);
        // EndShaderMode();
        EndMode3D();
        // GUI
        EndDrawing();
        cam.Update(GetFrameTime());
    }

    CloseWindow();

    return 0;
}