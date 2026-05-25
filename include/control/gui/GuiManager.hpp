#pragma once
#include "Sprite.hpp"
#include "core/AssetManager.hpp"
#include "raylib.h"
#include "vehicle/Vehicle.hpp"

#include <functional>

class GuiManager
{
  private:
    struct Button
    {
        std::string text;
        int id;
        std::function<int()> action;
    };
    enum class GuiState
    {
        None,
        Vehicles,
        MyOrders,
        FreeOrders
    };
    Rectangle m_dashboardRect;
    Sprite9Slice m_panel;
    Sprite9Slice m_tab;
    GuiState m_state;
    VehicleManager& m_vehicleManager;
    Font m_font;
    float paddingH = 10.0f;
    float paddingV = 10.0f;
    float itemWidth = 100.0f;
    float itemHeight = 80.0f;
    float tabHeight = 80.0f;

    std::vector<Button> m_dashboardButtons;

    Sprite garage;

    void Recalculate()
    {
        m_dashboardRect = {GetScreenWidth() / 4.0f * 3.0f, 0, GetScreenWidth() / 4.0f, (float)GetScreenHeight()};
        itemWidth = m_dashboardRect.width - (2 * paddingH);
    }

    Vector2 GetItemPosition(int itemNumber)
    {
        // startX is the same
        float startY = m_dashboardRect.y + paddingH + tabHeight;
        float itemY = startY + (itemNumber * (paddingV + itemHeight));

        return Vector2{m_dashboardRect.x + paddingH, itemY};
    }

  public:
    GuiManager(AssetManager& assetManager, VehicleManager& vehicleManager)
        : m_panel(assetManager.GetGuiPanel()),
          m_state(GuiState::Vehicles),
          m_vehicleManager(vehicleManager),
          m_font(assetManager.GetFont()),
          garage(assetManager.GetSprite("icon"))
    {
        Recalculate();
        m_tab.texture = m_panel.texture;
        m_tab.nPatchInfo = m_panel.nPatchInfo;
        m_tab.nPatchInfo.source.height -= 28;
        m_tab.nPatchInfo.bottom = 0;
        // 1st button
        m_dashboardButtons.emplace_back(Button{"1. tlacitko", 0, nullptr});
        // 2nd button
        m_dashboardButtons.emplace_back(Button{"2. tlacitko", 1, nullptr});
        // 3rd button
        m_dashboardButtons.emplace_back(Button{"3. tlacitko", 2, nullptr});
        // 4th button
        m_dashboardButtons.emplace_back(Button{"4. tlacitko", 3, nullptr});
    }
    int selectedTab = 1;
    void DrawDashboard()
    {
        // draw main dashboard window
        Rectangle realDashboardSize = m_dashboardRect;
        realDashboardSize.y += (itemHeight / 2);
        realDashboardSize.height -= (itemHeight / 2);
        DrawPanel(m_panel, realDashboardSize);
        // draw tab menu (buttons at the top of the dashboard - cards)

        Rectangle menuDestinationRect = {m_dashboardRect.x, m_dashboardRect.y, m_dashboardRect.width, tabHeight};
        float tabItemWidth = menuDestinationRect.width / m_dashboardButtons.size();
        // shared between tabs text - Y asis
        float tabTextCenterY = menuDestinationRect.y + menuDestinationRect.height / 2;
        for (size_t i = 0; i < m_dashboardButtons.size(); i++)
        {
            bool isTabActive = selectedTab == i;
            // draw tab
            Rectangle tabItemPosition = {menuDestinationRect.x + (i * tabItemWidth),
                                         menuDestinationRect.y,
                                         tabItemWidth,
                                         isTabActive ? tabHeight - 8 : tabHeight};
            if (CheckCollisionPointRec(GetMousePosition(), tabItemPosition) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                selectedTab = i;
            }
            DrawPanel(isTabActive ? m_tab : m_panel, tabItemPosition, isTabActive ? WHITE : GRAY);
            if (i == 0)
            {
                DrawTexturePro(garage.texture, garage.sourceRect, tabItemPosition, {0, 0}, 0, WHITE);
            }
            //  draw text
            Vector2 textSize = MeasureTextEx(m_font, m_dashboardButtons.at(i).text.c_str(), 20, 0);
            DrawTextPro(m_font,
                        m_dashboardButtons.at(i).text.c_str(),
                        {(tabItemPosition.x + tabItemWidth / 2), tabTextCenterY},
                        {textSize.x / 2, textSize.y / 2},
                        0,
                        20,
                        0,
                        WHITE);
        }

        // draw items inside
        switch (m_state)
        {
        case GuiState::None:
            /* code */
            break;

        case GuiState::Vehicles:
        {
            auto& vehicles = m_vehicleManager.GetAllVehicles();
            for (size_t i = 0; i < vehicles.size(); i++)
            {
                auto name = vehicles.at(i)->GetName();
                auto position = vehicles.at(i)->GetPosition();

                // draw simple panel
                Vector2 panelPosition = GetItemPosition(i);
                Rectangle panelDestination = {panelPosition.x, panelPosition.y, itemWidth, itemHeight};
                DrawPanel(m_panel, panelDestination);

                // draw car name - middle top of the item rectangle
                Vector2 textSize = MeasureTextEx(m_font, name.c_str(), 24, 0);
                Vector2 textOrigin = {textSize.x / 2, 0};
                Vector2 textPosition = {panelDestination.x + (panelDestination.width / 2), panelDestination.y + 3};
                float titleHeight = 6 + textSize.y;
                DrawTextPro(m_font, name.c_str(), textPosition, textOrigin, 0, 24, 0, WHITE);
                // draw buttons bottom of the item rectangle - entire item rectangle width
                const char* text = TextFormat("%.0f, %.0f", position.x, position.y);
                textSize = MeasureTextEx(m_font, text, 20, 0);
                textOrigin = {textSize.x / 2, textSize.y / 2};
                textPosition = {(itemWidth / 4) / 2 + panelDestination.x,
                                panelDestination.y + titleHeight + ((itemHeight - titleHeight) / 2)};
                DrawTextPro(m_font, text, textPosition, textOrigin, 0, 20, 0, WHITE);
            }
        }
        break;
        case GuiState::MyOrders:
            /* code */
            break;

        case GuiState::FreeOrders:
            /* code */
            break;

        default:
            break;
        }
    }
};
