#pragma once

#include "Sprite.hpp"
#include "core/AssetManager.hpp"
#include "vehicle/Vehicle.hpp"
#include "vehicle/VehicleManager.hpp"

#include <array>
#include <vector>

struct Padding
{
    float right;
    float top;
    float left;
    float bot;
};

enum class TabType
{
    Vehicles,
    Mainfests,
    Marketplace,
    Sabotages,
    COUNT
};
struct TabButton
{
    TabType tabType;
    Sprite sprite;
    Rectangle rect;
};
struct VehicleItem
{
};
class GuiDashboard
{
  private:
    VehicleManager& m_vehicleManager;

    Rectangle m_dashboardRect;
    Sprite9Slice m_backgroundSprite;
    Sprite9Slice m_lineSprite;
    Sprite9Slice m_backgroundBorder;
    Font m_font;
    Padding m_padding;
    Vector2 m_tabMenuSize;
    Vector2 m_itemSize;

    TabType m_selectedTab = TabType::Vehicles;

    std::vector<TabButton> m_tabButtons;
    std::array<const char*, 4> TAB_ICONS = {"tab vehicles", "tab mainfests", "tab marketplace", "tab sabotages"};
    std::array<const char*, 4> TAB_NAMES = {"Vehicles", "Delivery", "Offers", "Sabotages"};
    Sprite m_plus;
    void Recalculate();
    Rectangle GetItemRectangle(float startingY, int index)
    {
        Rectangle rec;
        rec.x = m_dashboardRect.x + m_padding.left;
        rec.y = startingY + (index * (m_itemSize.y + m_padding.bot));
        rec.width = m_itemSize.x;
        rec.height = m_itemSize.y;
        return rec;
    }

  public:
    GuiDashboard(AssetManager& am, VehicleManager& vm);
    ~GuiDashboard();

    void Draw();
};

GuiDashboard::GuiDashboard(AssetManager& am, VehicleManager& vm)
    : m_vehicleManager(vm),
      m_backgroundSprite(am.GetSpriteNP("background color")),
      m_font(am.GetFont()),
      m_padding({8, 8, 8, 8})
{
    m_plus = am.GetSprite("icon plus");
    m_lineSprite = am.GetSpriteNP("line horizontal");
    m_backgroundBorder = am.GetSpriteNP("background border");
    Recalculate();
    for (int i = 0; i < (int)TabType::COUNT; i++)
    {
        TabButton b;
        b.tabType = static_cast<TabType>(i);
        b.sprite = am.GetSprite(TAB_ICONS[i]);
        b.rect = {m_dashboardRect.x + (m_tabMenuSize.x * i), m_dashboardRect.y, m_tabMenuSize.x, m_tabMenuSize.y};
        m_tabButtons.emplace_back(b);
    }
}

GuiDashboard::~GuiDashboard() {}

void GuiDashboard::Recalculate()
{
    m_dashboardRect = {GetScreenWidth() / 4.0f * 3.0f, 0, GetScreenWidth() / 4.0f, (float)GetScreenHeight()};
    m_tabMenuSize.x = m_dashboardRect.width / 4;
    m_tabMenuSize.y = m_tabMenuSize.x;
    m_itemSize.x = m_dashboardRect.width - m_padding.left - m_padding.right;
    m_itemSize.y = 100.0f;
}

void GuiDashboard::Draw()
{
    Color wh = GetColor(0xB4C6D8FF);
    Color inac = GetColor(0x64748BFF);
    Color act = GetColor(0x1E2D4AFF);
    // background
    // 0x00E5FFFF nebo 0x38BDF8FF small highlight
    // 0x1E2D4AFF active
    // ice cyan 0x00E5FFFF - point of interest
    // pink 0xFF2A85FF - alert
    // warning text 0xFF6B6BFF
    // bright green 0x00F5B4FF - OK
    // black 0x0B0F19F8
    // gold 0xFF9F1CFF - money
    // glow = pnik/green/cyan + FFFFFF white in the center -> intense glow
    Color bor = GetColor(0xFF9F1CFF);
    Color back = GetColor(0x0B0F19F8);
    DrawSpriteNP(m_backgroundBorder, m_dashboardRect, bor);
    DrawSpriteNP(m_backgroundSprite, m_dashboardRect, back);

    // tabs
    for (auto& tab : m_tabButtons)
    {
        Rectangle imgRect = {tab.rect.x + m_padding.left,
                             tab.rect.y + m_padding.top,
                             tab.rect.width - (m_padding.left + m_padding.right),
                             tab.rect.height - (m_padding.top + m_padding.bot)};
        if (CheckCollisionPointRec(GetMousePosition(), tab.rect))
        {
            Color col = GetColor(0x161F30FF);
            DrawRectangleRounded(imgRect, 0.3f, 8, col);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                m_selectedTab = tab.tabType;
        }
        DrawSpriteRect(tab.sprite, imgRect, m_selectedTab == tab.tabType ? wh : inac);
    }
    // line
    Color divCol = GetColor(0x33476AFF);
    DrawSpriteNP(m_lineSprite,
                 {m_dashboardRect.x + 2 * m_padding.left,
                  m_dashboardRect.y + m_tabMenuSize.y,
                  m_dashboardRect.width - 2 * (m_padding.left + m_padding.right),
                  (float)m_lineSprite.texture.height},
                 divCol);
    // title
    Vector2 textSize = MeasureTextEx(m_font, TAB_NAMES[(int)m_selectedTab], 46, 0);
    DrawTextEx(m_font,
               TAB_NAMES[(int)m_selectedTab],
               {m_dashboardRect.x + m_padding.left, m_dashboardRect.y + m_tabMenuSize.y + m_padding.top},
               46,
               0,
               wh);
    // draw cross symbol = buy vehicle
    Color warnTxt = GetColor(0xFF0000FF);
    float buyCarIconX = m_dashboardRect.x + m_dashboardRect.width - m_padding.right - textSize.x / 2;
    Rectangle buyCarIconTarget = {buyCarIconX,
                                  m_dashboardRect.y + m_tabMenuSize.y + m_padding.top,
                                  textSize.y - 10,
                                  textSize.y - 10};
    if (m_selectedTab == TabType::Vehicles)
        DrawSpriteRect(m_plus, buyCarIconTarget, warnTxt);

    // items
    float yItemStartPos = m_dashboardRect.y + m_tabMenuSize.y + textSize.y + m_padding.top;
    switch (m_selectedTab)
    {
    case TabType::Vehicles:
    {
        const auto& vehicles = m_vehicleManager.GetAllVehicles();
        for (size_t i = 0; i < vehicles.size(); i++)
        {
            Rectangle r = GetItemRectangle(yItemStartPos + m_padding.top, i);
            DrawSpriteNP(m_backgroundSprite, r, act);
            DrawTextEx(m_font,
                       vehicles[i]->GetName().c_str(),
                       {r.x + m_padding.left, r.y + m_padding.top},
                       34,
                       0,
                       WHITE);
        }
    }
    break;

    case TabType::Mainfests:
        break;

    case TabType::Marketplace:
        break;

    case TabType::Sabotages:
        break;

    default:
        break;
    }
}