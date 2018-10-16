/**
 *\file actor.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef ACTOR_H
#define ACTOR_H

#include <iosfwd>
#include <functional>
#include <SDL2/SDL_mixer.h>

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
    
    std::vector<Mix_Music *> _sounds;
      
    std::vector<std::function<void(Actor *, float)>>   _actfct;
    std::vector<std::function<void(Actor *)>>          _effectfct;
    std::vector<std::function<void(Actor *, Actor *)>> _effectfct2;
    
  public:
    Actor();

    Actor(std::string name, float life)
      :_elem(nullptr), _life(life), _name(name) {}
    
    Actor(std::string name, float life, Position pos)
      :_position(pos),_elem(nullptr), _life(life), _name(name), _hitbox(&_position) { _orientation = N; }
    
    virtual ~Actor();

    virtual void setStage(Stage * stage) { _stage = stage; }

    virtual const std::string & getName() const { return _name; }

    /** Called by the stage for each step of the game */
    virtual void act(float dt);

    /** Called to draw the actor */
    virtual void update(Viewport const & vp);

    virtual Position & getPosition() { return _position; }
    virtual const Position & getPosition() const { return _position; }

    virtual Hitbox & getHitbox()  { return _hitbox; }

    virtual void effect();

    virtual void effect(Actor *);

    virtual bool isDead() const { return _life <= 0; }

    virtual void kill() { _life = 0; }

    virtual void addActStatement(std::function<void(Actor *, float)> fct) {_actfct.push_back(fct);}

    virtual void addEffectStatement(std::function<void(Actor *)> fct) {_effectfct.push_back(fct);}

    virtual void addEffectStatement(std::function<void(Actor *, Actor *)> fct) {_effectfct2.push_back(fct);}
   
    virtual void addSound(const char * path);

    /**
     *\fn virtual void playSound(unsigned int id)
     *\brief Play the sound of the object
     *\param id Identifier of the sound (an actor may have several sounds)
     */
    
    virtual void playSound(unsigned int id);
    
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
     *\param path The path of the sprite
     */
    
    virtual void loadSprite(const char path[]);

    /**
     *\fn virtual void loadSprite(int color[4])
     *\brief Create a square with the size of the actor
     *\param color The color of the square
     */
    
    virtual void loadSprite(int color[4]);
    
    /**
     *\fn virtual void loadSprite()
     *\brief How to load the sprite in the object
     */
    
    virtual void loadSprite() = 0;

    /**
     *\fn virtual void saveAnnexe(std::ofstream & out)
     *\brief Save data in the actor that contain other actor
     */
    
    virtual void saveAnnexe(std::ofstream & out) {}

    /**
     *\fn virtual void loadAnnexe(std::ifstream & in)
     *\brief Load the annexe of a actor
     */
    
    virtual void loadAnnexe(std::ifstream & in) {}
  };
  
}  // actor

#endif /* ACTOR_H */
