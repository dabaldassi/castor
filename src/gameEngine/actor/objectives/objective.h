/**
 *\file objective.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "../actor.h"

#define OBJ_FONT "../font/cs_regular.ttf"

namespace actor {

  class Objective : public Actor
  {
  protected:
    int _limit;
    int _current;
    int _id;
  public:
    Objective(){}
    Objective(std::string name, int limit, int id);
    
    virtual void update(Viewport const & vp);
    virtual void loadSprite();
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);

    bool isComplete() const { return _current >= _limit; }
  };

  class FoodObjective : public Objective
  {
  public:
    FoodObjective(){}
    FoodObjective(std::string name, int limit, int id, int event[]);

    virtual void act(float dt);
  };


}  // actor

#endif /* OBJECTIVE_H */
