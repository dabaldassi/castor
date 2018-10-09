/**
 *\file character.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef CHARACTER_H
#define CHARACTER_H

#include "../moveable.hpp"

namespace actor {

  /**
   *\class Character
   *\brief A character is someone with we can interact, control 
   */
  
  class Character : public Moveable
  {
  protected:
  public:
    Character(){}
    Character(std::string name, Position pos);
    
    // virtual void act(float dt){}
    virtual void effect() = 0;
    virtual void loadSprite() = 0;
    virtual void move(float dt = 0) = 0;
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual void loadAnnexe(std::ifstream & in){}
    virtual void saveAnnexe(std::ofstream & out){}
    virtual void update(Viewport const & vp);
    virtual void searchCollision();
  };

}  // Actor

#endif /* CHARACTER_H */
