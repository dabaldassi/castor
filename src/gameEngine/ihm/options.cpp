#include "SANDAL2.h"
#include "keyboard.h"
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
	ihm::Keyboard::binding[*id] = event.key.keysym.sym;
	run = false;
	break;
      case SDL_MOUSEBUTTONDOWN:
	ihm::Keyboard::binding[*id] = event.button.button;
	run = false;
	break;
      }
  }

  setTextElement(elem, ihm::Keyboard::getKeyName(ihm::Keyboard::binding[*id]).c_str());
  ihm::Keyboard::savebindings();
}

void keybindings()
{
  int w, h;

  getDimensionWindow(&w, &h);
  
  createBlock(0, 0, w, h, Color::black, Game::KB_D, 0);

  setDisplayCodeWindow(Game::KB_D);
  
  ihm::KeyBindingText::create("Droite", RIGHT, Game::KB_D);
  ihm::KeyBindingText::create("Gauche", LEFT, Game::KB_D);
  ihm::KeyBindingText::create("Avant", FORWARD, Game::KB_D);
  ihm::KeyBindingText::create("Attaque", ATTACK, Game::KB_D);
  ihm::KeyBindingText::create("Arriere", BACK, Game::KB_D);
  ihm::KeyBindingText::create("Carte", MAP, Game::KB_D);
  ihm::KeyBindingText::create("Interagir", INTERACT, Game::KB_D);
  ihm::KeyBindingText::create("Pause", PAUSE, Game::KB_D);
  
  for (int i = 0; i < NB_CUSTOM_KEYS; i++)
    ihm::KeyBindingButton::create(ihm::Keyboard::getKeyName(ihm::Keyboard::binding[i]).c_str(), i, Game::KB_D);
  
}

void ret()
{
  ihm::Keyboard::keys[PAUSE] = true;
}
