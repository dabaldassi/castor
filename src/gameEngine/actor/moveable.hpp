#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "actor.h"
#include "../viewport.h"

namespace actor {

  class Moveable : public Actor
  {
  private:
    std::vector<Actor *> _collisions;
  protected:
    float _speed;
  public:
    Moveable()
      :Actor() {}
    Moveable(const std::string & name, float life, const Position & p);
      
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual void loadSprite(const char path[]);
    virtual void loadSprite(int color[]) { Actor::loadSprite(color); };
    virtual void loadSprite(){};
    virtual void saveAnnexe(std::ofstream & ){}
    virtual void loadAnnexe(std::ifstream & ){}
    virtual void setSpeed(float speed) { _speed = speed; }
    virtual void move(float){}
    virtual void addItem(Item *){}
    virtual void removeItem(Item *){}
    
    virtual ~Moveable();
  };


}  // actor

#endif /* MOVEABLE_H */
