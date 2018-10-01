#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>

#include "../../SANDAL2/SANDAL2.h"

#define NB_KEYS 10
#define NB_CUSTOM_KEYS 8
#define KEY_FILE "kkb.bin"

typedef enum {
  RIGHT,
  LEFT,
  FORWARD,
  BACK,
  ATTACK,
  PAUSE,
  MAP,
  INTERACT,
  WHEEL_UP,
  WHEEL_DOWN
}Keys;


namespace ihm {
  
  /**
   *\struct Keyboard
   *\brief Handle all the keyboard and mouse event
   */

  struct Keyboard
  {
    static int  binding[NB_KEYS]; /* Binding used */
    static bool keys[NB_KEYS]; /* Which key has been pressed */

    static void init();
    static void onclick(int);
    static void keypressed(SDL_Keycode c);
    static void keyreleased(SDL_Keycode c);
    static void loadbindings();
    static void savebindings();
    static void wheel(int);
  
    /**
     *\fn static void getKeyName(const char key[], int id)
     *\brief Get the name of the key by its id
     *\param key Array of char in which will be wwritten the name
     */
    static std::string getKeyName(int id);
    static void search(int, bool);
  
  };

}  // ihm

#endif /* KEYBOARD_H */
