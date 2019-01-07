/**
 *\file game.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef GAME_H
#define GAME_H

#include "stage.h"

#define NB_OPTIONS 2

typedef enum {KEY_BINDING, RETURN}Options;

/**
 *\class Game
 *\brief Class which handle the event loop of the game
 */

class Game
{
private:
  
public:
  Stage stage;

  /* Display of the game */
  
  static constexpr int GAME_D = 0;
  static constexpr int PAUSE_D = 1;
  static constexpr int MENU_D = 2;
  static constexpr int OPTIONS_D = 3;
  static constexpr int KB_D = 3;
  
  Game();

  /**
   *\param w Width of the window
   *\param h Height of the window
   *\param name Name of the window
   */
  
  Game(int w, int h, const char * name);

  /**
   *\fn void run()
   *\brief Set the game in run mode 
   *\param generate Function to generate the stage. If you don't send one, it will call the generation by default. If you had already set one and call run again without the function, it will call the last function you added.
   */
  void run(std::function<void (Stage *)> generate = nullptr);

  /**
   *\fn void pause()
   *\brief Load the pause menu
   */
  void pause();

  /**
   *\fn void options()
   *\brief Load the option screen
   */
  void options();

  /**
   *\fn void event_manager(bool (*statement)());
   *\brief Loop and manage events while the game is running
   *\param statement Statement that will be executed 
   */
  void event_manager(bool (*statement)(float));

  
  virtual ~Game();
};

/**
 *\struct DataWindow
 *\brief Data relative to the window. 
 */

typedef struct
{
  Game * game; /* The current game running */
  int    param; /* 0 means should close window */
}DataWindow;


#endif /* GAME_H */
