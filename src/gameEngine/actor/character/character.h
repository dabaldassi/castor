#ifndef CHARACTER_H
#define CHARACTER_H

#include "../actor.h"

namespace actor {

  /**
   *\class Character
   *\brief A character is someone with we can interact, control 
   */
  
  class Character : public Actor
  {
  protected:
  public:
    Character(){}
    Character(std::string name, Position pos);
    
    virtual void act(float dt){}
    virtual void effect();
    virtual void loadSprite() = 0;
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual void loadAnnexe(std::ifstream & in){}
    virtual void saveAnnexe(std::ofstream & out){}
  };

}  // Actor

#endif /* CHARACTER_H */
