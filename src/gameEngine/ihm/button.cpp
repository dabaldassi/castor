#include "button.h"
#include "color.h"
#include "font.h"

using ihm::Button;
using ihm::OptionButton;
using ihm::KeyBindingButton;
using ihm::PauseButton;

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

void PauseButton::create(const char * text, int id, int d)
{
  int     * data;
  int       w,h;
  
  getDimensionWindow(&w, &h);
  Element * elem = Button::create(w/4, h * id/5.f, w/2, h/5, 50, FREE_MONO_BOLD, text, Color::white, SANDAL2_BLENDED, Color::black, d, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_pause);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
  setOnMouseMotionElement(elem, onmotion);
  setUnMouseMotionElement(elem, unmotion);
}

void OptionButton::create(const char *text, int id, int d)
{
  int     * data;
  int       w,h;

  getDimensionWindow(&w, &h);
  
  Element * elem = Button::create(w/4, h * id/6, w/2, h/6, 30, CS_REGULAR, text, Color::white, SANDAL2_BLENDED, Color::black, d, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_options);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
}

void KeyBindingButton::create(const char * text, int id, int d)
{
  int     * data = NULL;
  int       w,h;

  getDimensionWindow(&w, &h);
  
  Element * elem = Button::create(2*w/3, id*h/12.f, w/8, h / 12, 50, FREE_MONO , text, Color::white, SANDAL2_BLENDED, Color::black, d, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_keybind);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
}
