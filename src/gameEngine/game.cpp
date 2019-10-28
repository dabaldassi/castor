#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <SDL2/SDL_mixer.h>

#include "game.h"
#include "contactListener.h"

#include "ihm/keyboard.h"
#include "ihm/button.h"
#include "ihm/color.h"

#include "ihm/menu.h"

Game::Game():stage{0,0}
{}

Game::Game(int w, int h, const char * name):stage{w,h}
{
  int          black[4] = {0,0,0,0};
  DataWindow * dataw = (DataWindow *) malloc(sizeof(DataWindow));

  if(dataw)
    {
      dataw->game = this;
      dataw->param = 1;
    }

  setFreeDataWindow(free);
  
  if(initAllSANDAL2(IMG_INIT_JPG))
    {
      puts("Failed to init SANDAL2");
    }

  if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
      puts("Failed to init audio !");
    }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048) < 0)
    {
      puts("SDL_Mixer error");
    }

  createWindow(w, h, name, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/ SDL_WINDOW_RESIZABLE, black, GAME_D);
  
  if(!initIteratorWindow())
    {
      closeAllSANDAL2();
      fprintf(stderr, "Failed to open window \n");
      exit(0);
    }

  setDataWindow(dataw);

  ihm::Keyboard::init();
}

Game::~Game()
{
  Mix_Quit();
  closeAllWindow(); /* close all windows */
  closeAllSANDAL2();
}

/**
 *\fn bool run_statement()
 *\brief Statement which will be executed in run mode
 */

bool run_statement(float dt)
{
  DataWindow * data = NULL;

  initIteratorWindow();
  
  while(getDataWindow((void **)&data) && !nextWindow());
    
  if(!getDataWindow((void **)&data) && data)
    {
      if(ihm::Keyboard::keys[PAUSE])
	{
	  ihm::Keyboard::keys[PAUSE] = false;
	  data->game->pause();
	}
  
      data->game->stage.act(dt);
      data->game->stage.update();

    }
  
  return !data->game->stage.end();    
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

      Stage::world().Step(dt/1000.f, 10, 3);

      run = run && dataw->param;
      dataw->param = (run)?dataw->param:0;
      run = run && statement(dt);
      
      updateWindow();
      displayWindow();
      ticks = 16 - SDL_GetTicks() + tps;

      if(ticks > 0)
	SDL_Delay(ticks);

      if(!initIteratorWindow())
	run = false;
      
    }
}

void Game::run(std::function<void(Stage *)> generate)
{
  std::srand(std::time(nullptr));
  ContactListener contact;

  Stage::world().SetContactListener(&contact);
  
  if(generate) stage.setGenerate(generate);
  
  stage.generate();
  
  setDisplayCodeWindow(GAME_D);
  event_manager(run_statement);
  clearDisplayCode(GAME_D);

   Stage::world().SetContactListener(nullptr);
  //stage.save();
}

void Game::pause()
{
  int w,h;
  getDimensionWindow(&w,&h);
  ihm::Menu<PAUSE_D> menu_pause(w,h);

  menu_pause.setTitle("Pause");
  menu_pause.setBackground([](){});
  menu_pause.setTextColor(Color::white, Color::red);
  menu_pause.addItem("Continuer", []() { return false; });
  menu_pause.addItem("Quitter", []() {
      DataWindow * dataw;
      getDataWindow((void **)&dataw);
      dataw->param = 0;
      return false; });

  menu_pause.run();
  
  for (int i = 0; i < NB_KEYS; i++) { // Avoid interference with game display
    ihm::Keyboard::keys[i] = false;
  }
  
  clearDisplayCode(PAUSE_D);
  setDisplayCodeWindow(GAME_D);
}
