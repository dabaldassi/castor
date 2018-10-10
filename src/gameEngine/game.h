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
  
  /**
   *\fn void event_manager(bool (*statement)());
   *\brief Loop and manage events while the game is running
   *\param statement Statement that will be executed 
   */
  void event_manager(bool (*statement)(float));

public:
  Stage stage;
  
  static constexpr int GAME_D = 0;
  static constexpr int PAUSE_D = 1;
  static constexpr int MENU_D = 2;
  static constexpr int OPTIONS_D = 3;
  static constexpr int KB_D = 3;
  
  Game();
  Game(int w, int h);

  /**
   *\fn void run()
   *\brief Set the game in run mode 
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
