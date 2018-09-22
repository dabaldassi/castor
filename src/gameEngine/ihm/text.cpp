#include "../screen.h"
#include "text.h"
#include "color.h"

Element * Text::create(float x, float y, float width, float height, float textSize, const char *font, const char *text, int *textColor, int quality, int displayCode, int plan)
{
  return createText(x, y, width, height, textSize, font, text, textColor, quality, displayCode,plan);
}

void KeyBindingText::create(const char *text, int id)
{
  Text::create(WIDTH/3.f, id*HEIGHT/12.f, WIDTH/4, HEIGHT/12,50, FONT_KEYBIND, text, Color::white, SANDAL2_BLENDED, KB_D, 0);
}
