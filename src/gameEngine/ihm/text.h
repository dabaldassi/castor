#ifndef TEXT_H
#define TEXT_H

#include "../../SANDAL2/SANDAL2.h"

class Text
{
public:
  Text();

  static Element * create(float x, float y, float width, float height, float, const char *font, const char *text, int *textColor, int quality, int displayCode, int plan);
  
  virtual ~Text();
};


class KeyBindingText : public Text
{
public:
  KeyBindingText();

  static void create(const char * text, int id, int d);
  
  virtual ~KeyBindingText();
};


#endif /* TEXT_H */
