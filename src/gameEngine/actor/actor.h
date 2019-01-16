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
#include <Box2D/Dynamics/b2Body.h>
#include <vector>

#include "../viewport.h"
#include "../position.h"

#include "../../SANDAL2/Element.h"

class Stage;

b2Vec2 operator*(const b2Vec2 & v, float coeff);

namespace actor {

  class Actor;
  class Item;
  
  class Data
  {
    Actor * _actor;
    
  public:
    void setActor(Actor * actor);

    template<class Actor=Actor *>
    Actor getActor() { return dynamic_cast<Actor>(_actor);}
    
    /**
     *\brief The metb2Vec2 operator*(const b2Vec2 & vec, float coeff)
{
  return b2Vec2(vec.x*coeff, vec.y*coeff);
}hod to set the data free
     */
    static void free(void * e) { delete (Data *) e; }

    virtual ~Data() {}
  };


  
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
    b2Body   *  _body;
    
    std::vector<Mix_Chunk *> _sounds;
      
    std::vector<std::function<void(Actor *, float)>>   _actfct;
    std::vector<std::function<void(Actor *)>>          _effectfct;
    std::vector<std::function<void(Actor *, Actor *)>> _effectfct2;
    std::vector<std::function<void(Actor *, Actor *)>> _collisionOn;
    std::vector<std::function<void(Actor *, Actor *)>> _collisionOff;
    
  public:
    std::function<void(Actor *, int)> onClick;
    
    Actor();

    Actor(const std::string & name, float life);
    
    Actor(const std::string & name, float life, const Position & pos);
    
    virtual ~Actor();

    b2Body * body() { return _body; }

    const b2Body * body() const { return _body; }

    Element * elem() { return _elem; }

    const Element * elem() const { return _elem; }

    Stage * stage() { return _stage; }

    const Stage * stage() const { return _stage; }

    void setStage(Stage * stage) { _stage = stage; }

    virtual const std::string & getName() const { return _name; }

    /** Called by the stage for each step of the game */
    virtual void act(float dt);

    /** Called to draw the actor */
    virtual void update(Viewport const & vp);

    virtual float getLife() const { return _life; }
    
    virtual void effect();

    virtual void effect(Actor *);

    virtual bool isDead() const { return _life <= 0; }

    virtual void kill() { _life = 0; }

    virtual void addActStatement(const std::function<void(Actor *, float)> & fct) {_actfct.push_back(fct);}

    virtual void addEffectStatement(const std::function<void(Actor *)> & fct) {_effectfct.push_back(fct);}

    virtual void addEffectStatement(const std::function<void(Actor *, Actor *)> & fct) {_effectfct2.push_back(fct);}

    virtual void addCollisionOnStatement(const std::function<void(Actor *, Actor *)> & fct) {_collisionOn.push_back(fct);}
    
    virtual void addCollisionOffStatement(const std::function<void(Actor *, Actor *)> & fct) {_collisionOff.push_back(fct);}

    virtual void addOnClickEvent(std::function<void(Actor *, int)> fct);
   
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


    virtual void collisionOn(Actor * actor);

    virtual void collisionOff(Actor * actor);
    virtual void addItem(Item * item) = 0;
    virtual void removeItem(Item * item) = 0;

    /**
     *\fn virtual void setData(const D & data)
     *\brief Set a data to your actor
     *\param data A data of type Data or inheritance. Need to allocate with new (for now).
     */
    
    void setData(Data * data);

    /**
     *\fn virtual void getData()
     *\brief Get your data back
     */

    template<class Data=Data *>
    Data getData() const;

    virtual void takeDamage(float damage) { _life -= damage; }

    template<typename T=Position>
    std::enable_if_t<std::is_same<T,Position>::value,T>
    getPosition() { return _position; }

    template<typename T>
    std::enable_if_t<std::is_same<T,b2Vec2>::value,T>
    getPosition() { return _body->GetPosition() * Viewport::METER_TO_PIXEL; }
  };

  template<class Data=Data *>

  Data Actor::getData() const
  {
    Data d;

    getDataElement(_elem, (void **)&d);

    return d;
  }

}  // actor

#endif /* ACTOR_H */
