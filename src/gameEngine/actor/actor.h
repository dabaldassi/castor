/**
 *\file actor.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <fstream>

#include "../viewport.h"

#include "../../SANDAL2/Element.h"

#include "../hitbox.h"

class Stage;

namespace actor {

  /**
   *\class Actor
   *\brief Mother class of all the actors of the game
   */
  
  class Actor
  {
  protected:
    Stage    *  _stage;
    Position    _position;
    Element  *  _elem;
    float       _life;
    std::string _name;
    int         _orientation;
    Hitbox      _hitbox;
    
  public:
    Actor();

    Actor(std::string name, float life)
      :_elem(nullptr), _life(life), _name(name) {}
    
    Actor(std::string name, float life, Position pos)
      :_position(pos),_elem(nullptr), _life(life), _name(name), _hitbox(pos) { _orientation = N; }
    
    virtual ~Actor();

    void setStage(Stage * stage) { _stage = stage; }

    std::string getName() const { return _name; }

    /** Called by the stage for each step of the game */
    virtual void act(float dt) = 0;

    /** Called to draw the actor */
    virtual void update(Viewport const & vp);

    virtual Position getPosition() const { return _position; }

    virtual Hitbox getHitbox() const { return _hitbox; }

    virtual void effect() = 0;

    virtual bool isDead() const { return _life <= 0; }

    virtual void kill() { _life = 0; }

    /**
     *\fn virtual void save(std::ofstream & out)
     *\brief Save the data of the actor in a binary file
     *\param out Binary file in which will be written the data
     */
    
    virtual void save(std::ofstream & out);

    /**
     *\fn virtual void load(std::ifstream & in)
     *\brief Load data from a binary file
     *\param Binary file read
     */
    
    virtual void load(std::ifstream & in);

    /**
     *\fn virtual void loadSprite(const char path[])
     *\brief Load a sprite from a path. The name of the actor + .png will add to that path.
     */
    
    virtual void loadSprite(const char path[]);

    virtual void loadSprite() = 0;

    /**
     *\fn virtual void saveAnnexe(std::ofstream & out)
     *\brief Save data in the actor that contain other actor
     */
    
    virtual void saveAnnexe(std::ofstream & out){}

    /**
     *\fn virtual void loadAnnexe(std::ifstream & in)
     *\brief Load the annexe of a actor
     */
    
    virtual void loadAnnexe(std::ifstream & in){}
  };
  
}  // actor

#endif /* ACTOR_H */
