/**
 *\file building.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef BUILDING_H
#define BUILDING_H

#include "../static.h"

namespace actor {

  /**
   *\class Building
   *\brief Building on the map
   */
  
  class Building : public Static
  {
  protected:
    Position _trigger; /* Position where you can enter the building */
  public:
    Building(){}
    Building(std::string name, Position pos);
    
    virtual void effect();
    virtual void loadSprite() { Actor::loadSprite("../sprites/building/"); }
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
  };
  
}  // actor

#endif /* BUILDING_H */
