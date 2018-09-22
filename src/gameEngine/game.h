#ifndef GAME_H
#define GAME_H

#include "stage.h"

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
  
  Game();

  /**
   *\fn void run()
   *\brief Set the game in run mode 
   */
  void run();

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
  
  virtual ~Game(){}
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
