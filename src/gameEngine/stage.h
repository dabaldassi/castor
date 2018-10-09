/**
 *\file stage.h
 *\author dabaldassi
 *\date 07/2018
 */

#ifndef STAGE_H
#define STAGE_H

#include <memory>
#include <list>
#include "actor/actor.h"
#include "viewport.h"

#define FILE_SAVE "save.bin"
#define NB_OBJ_EVENT 1

namespace actor {

  class Controlable;
  
}  // Namespace

enum ObjectiveEvent { FOOD };

struct Stage {
  using ActorPtr = std::unique_ptr<actor::Actor>;
  using Actors = std::list<ActorPtr>;

private:
  Actors   _actors;
  Viewport _vp;
  int      _objectiveEvent[NB_OBJ_EVENT];
  std::function<void(Stage *)> gen;

public:
  actor::Controlable * player; /* Some actor need to interact with the player */
  
  /**
   * \param width the width of the windows
   * \param height the height of the windows
   */
  Stage(int width, int height);

  Viewport       & viewport()       { return _vp; }
  Viewport const & viewport() const { return _vp; }

  Actors const & actors() const { return _actors; }
  Actors       & actors()       { return _actors; }

  /** 
   * This method call the act() method for every actors managed by this stage
   * \param dt the time (in seconds) since the last call of act()
   */
  void act(float dt);

  /** This method call the update() method for every actors */
  void update() { for (auto & a : _actors) a->update(_vp); }

  /**
   * Construct inplace an actor and return a referecence to it
   * \param args parameters of the constructor of the actor type
   * \return the instance of the actor created
   */
  template <class A, class... Args>
  A & create(Args &&... args);

  void create(size_t hash);

  /** \param actor the actor to add to this stage */
  void add(ActorPtr && actor) { actor->setStage(this); _actors.push_back(std::move(actor)); }

  /** \param actor the actor to remove from the stage */
  void remove(ActorPtr & actor);

  /**
   *\fn void save()
   *\brief Save all the actor on the stage in a binary file. Call each save method of the actor
   */
  
  void save();

  /**
   *\fn void load()
   *\brief Load the actor on the stage by callling reading in the binary file 
   */
  
  void load();

  /**
   *\fn void generate()
   *\brief Generate the stage
   */
  
  void generate();

  /**
   *\fn void setGenerate(std::function<void(Stage * stage)> g)
   *\brief Set your own function to generate the stage
   */
  
  void setGenerate(std::function<void(Stage * stage)> g) { gen = g; } 

  //void eventObj(const actor::Food * food);
  int  getObjEvent(int event);
};


template <class A, class... Args>
A & Stage::create(Args &&... args)
{ 
  _actors.push_back(std::make_unique<A>(std::forward<Args>(args)...)); 
  A & a = *static_cast<A *>(_actors.back().get());
  a.setStage(this);
  return a;
}

#endif /* STAGE_H */
