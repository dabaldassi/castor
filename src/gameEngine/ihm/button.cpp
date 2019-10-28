#include "button.h"
#include "color.h"
#include "font.h"

using ihm::Button;

void onmotion(Element * e)
{
  setTextColorElement(e, Color::yellow);
}

void unmotion(Element * e)
{
  setTextColorElement(e, Color::white);
}

Element * Button::create(float x, float y, float width, float height, float texteSize, const char *font, const char *text, int *textColor, int quality, int *couleurBlock, int displayCode, int plan)
{
  Element * elem = NULL;

  elem = createButton(x, y, width, height, texteSize, font, text, textColor, quality, couleurBlock, displayCode, plan);

  addClickableElement(elem, rectangleClickable(0, 0, 1, 1), 0);

  return elem;
}
