#pragma once
#include "GuiHelper.hpp"
#include "Sprite.hpp"

#include "raylib.h"

#include <functional>
#include <string>

class GuiButton
{
  private:
    Rectangle m_targetRectangle;
    Padding m_padding;
    Sprite9Slice m_sprite;
    Sprite m_image;
    std::function<void()> m_callback;
    Color m_tint;

    std::string m_text;
    float m_textSize;
    Color m_textColor;
    Font m_font;
    bool m_isHovered;
    bool m_isClicked;

    Vector2 GetTextPosition();
    Vector2 GetTextOrigin();
    Rectangle GetContentArea();

  public:
    GuiButton(Rectangle targetRectangle,
              Padding padding,
              Sprite9Slice backGroundSprite,
              std::string text,
              float textSize,
              Font font,
              Sprite image,
              std::function<void()> callback,
              Color imageTint = WHITE,
              Color textColor = WHITE);
    ~GuiButton();

    void Update(MouseContext context, float deltaTime);

    void Draw();
};

Vector2 GuiButton::GetTextPosition() { return {m_targetRectangle.width / 2, m_targetRectangle.height / 2}; }
Vector2 GuiButton::GetTextOrigin() { return MeasureTextEx(m_font, m_text.c_str(), m_textSize, 0); }
Rectangle GuiButton::GetContentArea()
{
    return {m_targetRectangle.x + m_padding.left,
            m_targetRectangle.y + m_padding.top,
            m_targetRectangle.width - (m_padding.right + m_padding.left),
            m_targetRectangle.height - (m_padding.top + m_padding.bot)};
}
GuiButton::GuiButton(Rectangle targetRectangle,
                     Padding padding,
                     Sprite9Slice backGroundSprite,
                     std::string text,
                     float textSize,
                     Font font,
                     Sprite image,
                     std::function<void()> callback,
                     Color imageTint,
                     Color textColor)
    : m_targetRectangle(targetRectangle),
      m_padding(padding),
      m_sprite(backGroundSprite),
      m_text(std::move(text)),
      m_textSize(textSize),
      m_font(font),
      m_image(image),
      m_callback(std::move(callback)),
      m_tint(imageTint),
      m_textColor(textColor)
{
}

GuiButton::~GuiButton() {}

void GuiButton::Update(MouseContext context, float deltaTime)
{
    if (CheckCollisionPointRec(context.position, m_targetRectangle))
    {
        m_isHovered = true;
        if (context.leftPressed)
        {
            if (m_callback)
                m_callback();
        }
    }
    else
    {
        m_isHovered = false;
    }
}

void GuiButton::Draw()
{
    DrawSpriteNP(m_sprite, m_targetRectangle);
    if (IsTextureValid(m_image.texture))
        DrawSpriteRect(m_image, GetContentArea());
    DrawTextPro(m_font, m_text.c_str(), GetTextPosition(), GetTextOrigin(), 0, m_textSize, 0, m_textColor);
}
