/**
 *\file controlable.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef CONTROLABLE_H
#define CONTROLABLE_H

#include "character.h"
#include "../items/item.h"

#define INIT_SPEED_CONTROLABLE 3.f

namespace actor {

  /**
   *\class Controlable
   *\brief The character you play
   */
  
  class Controlable : public Character
  {
  private:
    float      _speed;
  public:
    Controlable(){}
    Controlable(std::string name, Position pos);
    
    virtual void act(float dt);
    virtual void effect(){}
    virtual void loadSprite();
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
    virtual void loadAnnexe(std::ifstream & in);
    virtual void saveAnnexe(std::ofstream & out);
    virtual void moveCamera();
    virtual void searchCollision();
    virtual void move();
  };

  
}  // actor

#endif /* CONTROLABLE_H */
