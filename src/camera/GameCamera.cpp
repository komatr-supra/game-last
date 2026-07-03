#include "GameCamera.hpp"

#include "Config.hpp"
#include "raylib.h"
#include "raymath.h"
#include "world/WorldObjectBase.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

namespace game::camera
{
void GameCamera::CalculateCameraPosition()
{
    Vector3 cameraAnchorVec3 = m_cameraAnchor.GetPosition();
    m_camera.position = Vector3{cameraAnchorVec3.x + game::constant::settings::camOffsetX,
                                game::constant::settings::camOffsetY,
                                cameraAnchorVec3.z + game::constant::settings::camOffsetZ};
    m_camera.target = cameraAnchorVec3;
}
GameCamera::GameCamera(game::world::WorldObject& cameraAnchor) : m_cameraAnchor(cameraAnchor)
{
    CalculateCameraPosition();
    m_camera.up = Vector3{0.0f, 1.0f, 0.0f};
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void GameCamera::Update(float deltaTime)
{
    // move camera directly
    // camera.position = cameraAnchor.position + offset;

    // light shader data
    float camPos[3] = {m_camera.position.x, m_camera.position.y, m_camera.position.z};
    SetShaderValue(m_lightingShader, m_lightingShader.locs[SHADER_LOC_VECTOR_VIEW], camPos, SHADER_UNIFORM_VEC3);

    // TODO: move to anchor
    /*
    if (m_moveTween.progress() < 1.0f)
    {
        auto current = m_moveTween.step(static_cast<int>(deltaTime * 1000));
        m_camera.target.x = current[0];
        m_camera.target.z = current[1];
    }
    else
    {
        ShowCursor();
    }
        */

    // last step = set to position
    CalculateCameraPosition();
}
void GameCamera::Init()
{
    m_lightingShader = LoadShader(TextFormat("assets/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                                  TextFormat("assets/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    m_lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(m_lightingShader, "viewPos");
    // member ambient loc, refactor to method, Color as parameter and calculate inside color.r / 255.0f....
    int ambientLoc = GetShaderLocation(m_lightingShader, "ambient");
    float ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    SetShaderValue(m_lightingShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    // create a Sun
    m_lightWorld = CreateLight(LIGHT_DIRECTIONAL, {-10, 30, 20}, Vector3Zero(), GRAY, m_lightingShader);
}
} // namespace game::camera