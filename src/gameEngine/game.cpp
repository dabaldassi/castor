#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "game.h"
#include "screen.h"
#include "stage.h"

#include "ihm/keyboard.h"
#include "ihm/button.h"
#include "ihm/options.h"
#include "ihm/color.h"

Game::Game():stage{WIDTH, HEIGHT}
{}

/**
 *\fn bool run_statement()
 *\brief Statement which will be executed in run mode
 */

bool run_statement(float dt)
{
  DataWindow  * data = NULL;

  if(!getDataWindow((void **)&data) && data)
    {
      if(Keyboard::keys[PAUSE])
	{
	  Keyboard::keys[PAUSE] = false;
	  data->game->pause();
	}
  
      data->game->stage.act(dt);
      data->game->stage.update();
    }
  
 return true;    
}

/**
 *\fn bool run_statement()
 *\brief Statement which will be executed in pause mode
 */

bool pause_statement(float dt)
{
  bool          ret = true;
  DataWindow  * data = NULL;

  if(Keyboard::keys[PAUSE])
    {
      Keyboard::keys[PAUSE] = false;
      ret = false;
    }
  else
    {
      if(!getDataWindow((void **)&data) && data)
	{
	  switch(data->param)
	    {
	    case -1:
	      ret = false; /* To quit the pause loop */
	      data->param = 1; /* Reset the default value */
	    case 2:
	      data->param = 1;
	      data->game->options();
	      break;
	    default:
	      break;
	    }
	}
    }

  return ret;
}

bool options_statement(float dt)
{
  int d;
  
  if(Keyboard::keys[PAUSE])
    {
      getDisplayCodeWindow(&d);
      Keyboard::keys[PAUSE] = false;

      /* If it's the not the option menu display, clear the current display and set the option menu */
      if(d != OPTIONS_D)
	{
	  clearDisplayCode(d);
	  setDisplayCodeWindow(OPTIONS_D);
	}
      else
	return false;
    }
  return true;
}

void click_pause(Element * elem, int c)
{
  int        * data  = NULL;
  DataWindow * dataw = NULL;

  if(!getDataElement(elem, (void **)&data) && data && !getDataWindow((void **)&dataw) && dataw)
    {
      switch(*data)
	{
	case 1: /* Return to the game */
	  dataw->param = -1;
	  break;
	case 2: /* Lauch option menu */
	  dataw->param = 2;
	  break;
	case 3: /* Quit */
	  dataw->param = 0;
	  break;
	}
    }
}

void click_options(Element * elem, int c)
{
  void (*options[])() = {keybindings, ret};
  int  * data = NULL;

  if(!getDataElement(elem, (void **)&data) && data)
    {
      options[*data]();
    }
}

void Game::event_manager(bool (*statement)(float))
{
  int          tps, ticks, oldTps = 0;
  float        dt;
  bool         run = true;
  DataWindow * dataw;
  
  while(run)
    {
      tps = SDL_GetTicks();
      dt = tps - oldTps;
      oldTps = tps;
      
      run = !PollEvent(NULL);
      
      getDataWindow((void **)&dataw);
      
      run = run && dataw->param;
      dataw->param = (run)?dataw->param:0;
      run = run && statement(dt);
      
      updateWindow();
      displayWindow();
      ticks = 16 - SDL_GetTicks() + tps;

      if(ticks > 0)
	SDL_Delay(ticks);

      if(initIteratorWindow())
	run = false;
      
    }
  
}

void Game::run()
{
  std::srand(std::time(nullptr));
  
  stage.generate();
  //stage.load();
  
  setDisplayCodeWindow(GAME);
  event_manager(run_statement);
  clearDisplayCode(GAME);
  stage.save();
}

void Game::pause()
{
  createBlock(0, 0, WIDTH, HEIGHT, Color::black, PAUSE_D, 0);

  PauseButton::create("Continuer", 1, PAUSE_D);
  PauseButton::create("Option", 2, PAUSE_D);
  PauseButton::create("Quitter",3, PAUSE_D);

  //elem = createButton(0, 0, 100, 50, 20, FONT_PAUSE, text, textColor, quality, couleurBlock, displayCode, plan);

  setDisplayCodeWindow(PAUSE_D);

  event_manager(pause_statement);

  for (int i = 0; i < NB_KEYS; i++) { // Avoid interference with game display
    Keyboard::keys[i] = false;
  }
  
  clearDisplayCode(PAUSE_D);
  setDisplayCodeWindow(GAME);
}

void Game::options()
{
  createBlock(0, 0, WIDTH, HEIGHT, Color::black, OPTIONS_D, 0);

  setDisplayCodeWindow(OPTIONS_D);

  OptionButton::create("Clavier/souris", KEY_BINDING, OPTIONS_D);
  OptionButton::create("Retour", RETURN, OPTIONS_D);

  event_manager(options_statement);
  
  clearDisplayCode(OPTIONS_D);
  setDisplayCodeWindow(PAUSE_D);
}
