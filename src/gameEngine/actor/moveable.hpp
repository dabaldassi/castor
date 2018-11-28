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
    Moveable(std::string name, float life, Position p):
      Actor(name, life, p) {}

    //virtual void act(float dt) = 0;
    //virtual void update(Viewport const & vp);
    virtual void load(std::ifstream & in);
    virtual void save(std::ofstream & out);
    virtual void loadSprite(const char path[]);
    virtual void loadSprite() = 0;
    virtual void saveAnnexe(std::ofstream & out){}
    virtual void loadAnnexe(std::ifstream & in){}
    virtual void setSpeed(float speed) { _speed = speed; }
    
    virtual void move(float dt=0) = 0;
    
    virtual void searchCollision();
    
    
    virtual ~Moveable();
  };


}  // actor

#endif /* MOVEABLE_H */
