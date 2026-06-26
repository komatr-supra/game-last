#include "GameCamera.hpp"

#include "raylib.h"
#include "raymath.h"
#include "tween.h"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

namespace game::graphics
{
GameCamera::GameCamera() : m_trackedPosition(nullptr), m_desiredPosition{0, 0, 0}, m_moveDir{0, 0}
{
    m_camera.position = Vector3{0.0f, 0.0f, 0.0f};
    m_camera.target = Vector3{0.0f, 0.0f, 0.0f};
    m_camera.up = Vector3{0.0f, 1.0f, 0.0f};
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void GameCamera::CalculatePosition()
{
    m_camera.fovy = m_fovy;
    m_camera.position.x = m_camera.target.x + m_radius * cosf(m_pitch) * sinf(m_yaw);
    m_camera.position.y = m_camera.target.y + m_radius * sinf(m_pitch);
    m_camera.position.z = m_camera.target.z + m_radius * cosf(m_pitch) * cosf(m_yaw);
}

void GameCamera::Follow(const Vector3* target)
{
    if (target)
    {
        // m_trackedPosition = target;
        HideCursor();
        SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

        m_moveTween.from(m_camera.target.x, m_camera.target.z).to(target->x, target->z).during(400).via(tweeny::easing::cubicInOut);
    }
}

void GameCamera::Unfollow()
{
    m_desiredPosition = m_camera.target;
    m_trackedPosition = nullptr;
}

void GameCamera::Move(Vector2 direction)
{
    Unfollow();
    m_moveDir = direction;
}

void GameCamera::Update(float deltaTime)
{
    float camPos[3] = {m_camera.position.x, m_camera.position.y, m_camera.position.z};
    SetShaderValue(m_lightingShader, m_lightingShader.locs[SHADER_LOC_VECTOR_VIEW], camPos, SHADER_UNIFORM_VEC3);

    if (m_trackedPosition) { m_desiredPosition = *m_trackedPosition; }
    else if (m_moveDir != Vector2Zero())
    {
        m_desiredPosition.x += m_moveDir.x * m_camSpeed * deltaTime;
        m_desiredPosition.z += m_moveDir.y * m_camSpeed * deltaTime;
    }
    float wheel = GetMouseWheelMove();
    // TraceLog(LOG_WARNING, "wheel input: %f", wheel);
    m_radius += wheel;
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
    // m_camera.target = Vector3Lerp(m_camera.target, m_desiredPosition, deltaTime * 0.005f);
    CalculatePosition();
}
void GameCamera::Init()
{
    CalculatePosition();

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
} // namespace game::graphics