#ifndef BUTTON_H
#define BUTTON_H

#include "SANDAL2.h"

void click_pause(Element * elem, int);

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

  /**
   *\class PauseButton
   *\brief Button that will be dislayed on the pause screen
   */

  class PauseButton : public Button
  {
  public:
    PauseButton(){}

    static void create(const char * text, int id, int d);
  
    virtual ~PauseButton(){}
  };
  
}  // ihm

#endif /* BUTTON_H */
