#include "../../SANDAL2/SANDAL2.h"
#include "keyboard.h"
#include "../screen.h"
#include "color.h"
#include "text.h"
#include "button.h"
#include "../game.h"

/**
 *\fn void click_keybind(Element * elem)
 *\brief When one key is clicked, set a new one when key is down
 *\todo verify if binding exists
 */

void click_keybind(Element * elem,int c)
{
  SDL_Event   event;
  bool        run = true;
  int       * id;

  getDataElement(elem, (void **)&id);

  while (run) {
    SDL_WaitEvent(&event);

    switch(event.type)
      {
      case SDL_KEYDOWN:
	Keyboard::binding[*id] = event.key.keysym.sym;
	run = false;
	break;
      case SDL_MOUSEBUTTONDOWN:
	Keyboard::binding[*id] = event.button.button;
	run = false;
	break;
      }
  }

  setTextElement(elem, Keyboard::getKeyName(Keyboard::binding[*id]).c_str());
  Keyboard::savebindings();
}

void keybindings()
{
  createBlock(0, 0, WIDTH, HEIGHT, Color::black, KB_D, 0);

  setDisplayCodeWindow(KB_D);
  
  KeyBindingText::create("Droite", RIGHT);
  KeyBindingText::create("Gauche", LEFT);
  KeyBindingText::create("Avant", FORWARD);
  KeyBindingText::create("Attaque", ATTACK);
  KeyBindingText::create("Arriere", BACK);
  KeyBindingText::create("Carte", MAP);
  KeyBindingText::create("Interagir", INTERACT);
  KeyBindingText::create("Pause", PAUSE);
  
  for (int i = 0; i < NB_CUSTOM_KEYS; i++)
    KeyBindingButton::create(Keyboard::getKeyName(Keyboard::binding[i]).c_str(), i);
  
}

void ret()
{
  Keyboard::keys[PAUSE] = true;
}
