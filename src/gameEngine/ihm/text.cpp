#include "text.h"
#include "color.h"
#include "font.h"

Element * Text::create(float x, float y, float width, float height, float textSize, const char *font, const char *text, int *textColor, int quality, int displayCode, int plan)
{
  return createText(x, y, width, height, textSize, font, text, textColor, quality, displayCode,plan);
}

void KeyBindingText::create(const char *text, int id, int d)
{
  int w, h;

  getDimensionWindow(&w, &h);
  
  Text::create(w/3.f, id*h/12.f, w/4, h/12,50, FREE_MONO, text, Color::white, SANDAL2_BLENDED, id, 0);
}
