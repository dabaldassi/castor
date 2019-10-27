#include "text.h"
#include "color.h"
#include "font.h"

using ihm::Text;

Element * Text::create(float x, float y, float width, float height, float textSize, const char *font, const char *text, int *textColor, int quality, int displayCode, int plan)
{
  return createText(x, y, width, height, textSize, font, text, textColor, quality, displayCode,plan);
}
