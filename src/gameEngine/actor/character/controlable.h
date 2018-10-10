/**
 *\file controlable.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef CONTROLABLE_H
#define CONTROLABLE_H

#include "character.h"

#define INIT_SPEED_CONTROLABLE 3.f

namespace actor {

  /**
   *\class Controlable
   *\brief The character you play
   */
  
  class Controlable : public Character
  {
  public:
    Controlable(){}
    Controlable(std::string name, Position pos);

    virtual void act(float dt);
    virtual void loadSprite();
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
    virtual void loadAnnexe(std::ifstream & in);
    virtual void saveAnnexe(std::ofstream & out);
    virtual void moveCamera();
    virtual void move(float dt = 0);
  };

  
}  // actor

#endif /* CONTROLABLE_H */
