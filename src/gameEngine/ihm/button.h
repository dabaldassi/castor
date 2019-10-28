#ifndef BUTTON_H
#define BUTTON_H

#include "SANDAL2.h"

namespace ihm {

  /**
   *\class Button
   *\brief Manage a button with SANDAL2
   */

  class Button
  {
  private:
  public:
  
    static Element * create(float x, float y, float width, float height, float texteSize, const char *font, const char *text, int *textColor, int quality, int *couleurBlock, int displayCode, int plan);
    virtual ~Button(){}
  };

}  // ihm

#endif /* BUTTON_H */
