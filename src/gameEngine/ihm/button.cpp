#include "button.h"
#include "color.h"
#include "../screen.h"

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

void PauseButton::create(const char * text, int id)
{
  int     * data;
  Element * elem = Button::create(WIDTH/4, HEIGHT * id/5.f, WIDTH/2, HEIGHT/5, 50, FONT_PAUSE, text, Color::white, SANDAL2_BLENDED, Color::black, PAUSE_D, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_pause);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
  setOnMouseMotionElement(elem, onmotion);
  setUnMouseMotionElement(elem, unmotion);
}

void OptionButton::create(const char *text, int id)
{
  int     * data;
  Element * elem = Button::create(WIDTH/4, HEIGHT * id/6, WIDTH/2, HEIGHT/6, 30, FONT_OPTIONS, text, Color::white, SANDAL2_BLENDED, Color::black, OPTIONS_D, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_options);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
}

void KeyBindingButton::create(const char * text, int id)
{
  int     * data = NULL;
  Element * elem = Button::create(2*WIDTH/3, id*HEIGHT/12.f, WIDTH/8, HEIGHT / 12, 50, FONT_KEYBIND, text, Color::white, SANDAL2_BLENDED, Color::black, KB_D, 0);

  data = (int *) malloc(sizeof(int));
  *data = id;

  setOnClickElement(elem, click_keybind);
  setDataElement(elem, data);
  setFreeDataElement(elem, free);
}
