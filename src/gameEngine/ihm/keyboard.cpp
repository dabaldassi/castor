#include "keyboard.h"

using ihm::Keyboard;

bool Keyboard::keys[NB_KEYS];
int  Keyboard::binding[NB_KEYS];

void Keyboard::init()
{
  /* All keys shall be released at first */

  for(int i=0; i< NB_KEYS; i++)
    Keyboard::keys[i] = false;

  /* Init default keys */

  binding[RIGHT]      = SDLK_d;
  binding[LEFT]       = SDLK_q;
  binding[FORWARD]    = SDLK_z;
  binding[BACK]       = SDLK_s;
  binding[PAUSE]      = SDLK_ESCAPE;
  binding[MAP]        = SDLK_m;
  binding[INTERACT]   = SDLK_z;
  binding[ATTACK]     = SDL_BUTTON_LEFT;

  /* Set function that will be called when an event occured */

  setOnClickWindow(keypressed);
  setUnClickWindow(keyreleased);
  setKeyPressedWindow(keypressed);
  setKeyReleasedWindow(keyreleased);
  setWheelWindow(wheel);

  /* Load the customs bindings if they exist */
  
  loadbindings();
}

void Keyboard::wheel(int y)
{
  if(y==-1) keys[WHEEL_UP] = true;
  else keys[WHEEL_DOWN] = true;
}

void Keyboard::search(int c, bool b)
{
  int i = 0;

  while(c != binding[i] && i< NB_KEYS)
    ++i;

  if(i < NB_KEYS)
    keys[i] = b;
}

void Keyboard::keypressed(SDL_Keycode c)
{
  search(c, true);
}

void Keyboard::keyreleased(SDL_Keycode c)
{
  search(c, false);
}

void Keyboard::loadbindings()
{
  FILE * f = fopen(KEY_FILE, "rb");

  if(f != NULL)
    {
      fread(binding, sizeof(int), NB_KEYS, f);
      fclose(f);
    }
  else
    std::cerr << "Can't load keyboard bindings" << "\n";
}

void Keyboard::savebindings()
{
  FILE * f = fopen(KEY_FILE, "wb");
  
  if(f != NULL)
    {
      fwrite(binding, sizeof(int), NB_KEYS, f);
      fclose(f);
    }
  else
    std::cerr << "Can't save keyboard bindings" << "\n";
}

std::string Keyboard::getKeyName(int id)
{
  std::string s;
  
  switch(id)
    {
    case SDLK_ESCAPE:
      s = "ESC";
      break;
    case SDLK_TAB:
      s = "TAB";
      break;
    case SDLK_LSHIFT:
      s = "LSHIFT";
      break;
    case SDLK_RSHIFT:
      s = "RSHIFT";
      break;
    case SDLK_LCTRL:
      s = "LCTRL";
      break;
    case SDLK_RCTRL:
      s = "RCTRL";
      break;
    case SDLK_BACKSPACE:
      s = "BACK";
      break;
    case SDLK_LALT:
      s = "ALT";
      break;
    case SDLK_RALT:
      s = "ALTGR";
      break;
    case SDLK_LEFT:
      s = "LEFT";
      break;
    case SDLK_RIGHT:
      s = "RIGHT";
      break;
    case SDLK_UP:
      s = "UP";
      break;
    case SDLK_DOWN:
      s = "DOWN";
      break;
    case SDLK_RETURN:
      s = "ENT";
      break;
    case SDL_BUTTON_LEFT:
      s = "MB1";
      break;
    case SDL_BUTTON_RIGHT:
      s = "MB2";
      break;
    default:
      s = id;
      break;
    }

  return s;
}
