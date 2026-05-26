#pragma once

#include "Sprite.hpp"
#include "core/AssetManager.hpp"

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
    TakenContracts,
    AvaliableContracts,
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
    Rectangle m_dashboardRect;
    Sprite9Slice m_backgroundSprite;
    Font m_font;
    Padding m_padding;
    Vector2 m_tabMenuSize;
    Vector2 m_itemSize;

    TabType m_selectedTab = TabType::Vehicles;

    std::vector<TabButton> m_tabButtons;
    std::array<const char*, 4> TAB_ICONS = {"gui_tab_vehicles",
                                            "gui_tab_mainfests",
                                            "gui_tab_marketplace",
                                            "gui_tab_sabotages"};
    std::array<const char*, 4> TAB_NAMES = {"Vehicles", "Owned Contracts", "Avaliable Contracts", "Sabotages"};
    void Recalculate();

  public:
    GuiDashboard(AssetManager& am);
    ~GuiDashboard();

    void Draw();
};

GuiDashboard::GuiDashboard(AssetManager& am)
    : m_backgroundSprite(am.GetGuiPanel()), m_font(am.GetFont()), m_padding({8, 8, 8, 8})
{
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
    m_itemSize.x = m_dashboardRect.width;
    m_itemSize.y = 100.0f;
}

void GuiDashboard::Draw()
{
    // background
    DrawSpriteNP(m_backgroundSprite, m_dashboardRect);

    // tabs
    for (auto& tab : m_tabButtons)
    {
        Rectangle imgRect = {tab.rect.x + m_padding.left,
                             tab.rect.y + m_padding.top,
                             tab.rect.width - (m_padding.left + m_padding.right),
                             tab.rect.height - (m_padding.top + m_padding.bot)};
        if (CheckCollisionPointRec(GetMousePosition(), tab.rect))
        {
            Color col = ColorAlpha(LIGHTGRAY, 0.2f);
            DrawRectangleRounded(imgRect, 0.3f, 8, col);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                m_selectedTab = tab.tabType;
        }
        DrawSpriteRect(tab.sprite, imgRect, m_selectedTab == tab.tabType ? WHITE : GRAY);
    }

    // title
    DrawTextEx(m_font,
               TAB_NAMES[(int)m_selectedTab],
               {m_dashboardRect.x + m_padding.left, m_dashboardRect.y + m_tabMenuSize.y},
               46,
               0,
               WHITE);

    // items
    switch (m_selectedTab)
    {
    case TabType::Vehicles:

        break;

    default:
        break;
    }
}