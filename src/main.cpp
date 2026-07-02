#include "Config.hpp"
#include "core/AssetManager.hpp"
#include "graphics/GameCamera.hpp"
#include "gui/GuiManager.hpp"
#include "imgui.h"
#include "raylib.h"
#include "vehicles/VehicleManager.hpp"
#include "world/World.hpp"

int main(void)
{
    // ******************
    //   INITIALIZATION
    // ******************
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(game::constant::settings::winWidth, game::constant::settings::winHeight, "STD");
    SetTargetFPS(60);

    game::core::AssetManager am;
    am.Init();
    // TODO: add controller (input handler)
    game::world::World world(am);
    world.Init();
    game::camera::GameCamera cam(world);
    cam.Init();
    game::vehicles::VehicleManager vm(am, world);
    vm.Init();
    game::gui::GuiManager gui(vm, cam);
    gui.Init();

    // ******************
    //     GAME LOOP
    // ******************
    while (!WindowShouldClose())
    {
        // **************
        // SHADERS
        // **************

        // ******************
        //       LOGIC
        // ******************
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureMouse)
        {
            // game will capture inputs
        }
        cam.Update(GetFrameTime());

        // ******************
        //      DRAWING
        // ******************
        BeginDrawing();
        ClearBackground(GRAY);

        // WORLD (3D draw)
        BeginMode3D(cam.GetCam());
        world.Draw();
        vm.DrawAllVehicles();
        EndMode3D();

        // GUI
        gui.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}