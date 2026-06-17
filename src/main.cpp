#include "Config.hpp"
#include "core/AssetManager.hpp"
#include "graphics/Camera.hpp"
#include "vehicles/Vehicle.hpp"
#include "vehicles/VehicleManager.hpp"
#include "world/World.hpp"

#include "raylib.h"
#include "raymath.h"
#include <imgui.h>
#include <rlImGui.h>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(game::constant::settings::winWidth, game::constant::settings::winHeight, "STD");
    SetTargetFPS(60);
    rlImGuiSetup(true);
    game::core::AssetManager am;
    am.Init();
    game::graphics::GameCamera cam;
    game::world::World map(am);
    game::vehicles::VehicleManager vm(am);

    Shader lightingShader = LoadShader(TextFormat("assets/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                                       TextFormat("assets/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightingShader, "viewPos");
    int ambientLoc = GetShaderLocation(lightingShader, "ambient");
    float ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    SetShaderValue(lightingShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    Light light = CreateLight(LIGHT_DIRECTIONAL, {-10, 30, 20}, Vector3Zero(), GRAY, lightingShader);

    while (!WindowShouldClose())
    {
        float camPos[3] = {cam.GetCam().position.x, cam.GetCam().position.y, cam.GetCam().position.z};
        SetShaderValue(lightingShader, lightingShader.locs[SHADER_LOC_VECTOR_VIEW], camPos, SHADER_UNIFORM_VEC3);
        BeginDrawing();
        ClearBackground(GRAY);
        // 3D
        BeginMode3D(cam.GetCam());
        map.Draw();

        EndMode3D();
        // GUI
        rlImGuiBegin();
        ImGui::Text("im gui text obycejny");
        ImGui::Separator();
        ImGui::Button("tlacitko jak svina");
        ImGui::Text("dalsi text");
        rlImGuiEnd();
        EndDrawing();
        cam.Update(GetFrameTime());
    }
    CloseWindow();
    return 0;
}