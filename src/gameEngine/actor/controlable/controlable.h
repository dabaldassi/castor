/**
 *\file controlable.h
 *\author dabaldassi
 *\date 07/2018
 */


#ifndef CONTROLABLE_H
#define CONTROLABLE_H

#include "../moveable.hpp"

namespace actor {
  
  /**
   *\class Controlable
   *\brief The character you play
   */
  
  class Controlable : public Moveable
  {
  protected:
    int        _id; // id of the controlable (1 keyboard_1, 2, keyboard_2)
    bool       _keyboard; // If the controlable use the keyboard/mouse or joysticks
    static int _nb_controlable_keyboard; // Number of controlable created
  public:
    static constexpr float INIT_SPEED_CONTROLABLE = 7.f / Viewport::METER_TO_PIXEL;
    
    Controlable(){}
    Controlable(const std::string & name, float life, const Position & pos, bool keyboard = true);

    virtual void act(float dt);
    virtual void loadSprite();
    virtual void save(std::ofstream & out);
    virtual void load(std::ifstream & in);
    virtual void loadAnnexe(std::ifstream & in);
    virtual void saveAnnexe(std::ofstream & out);

    /**
     *\fn void moveCamera()
     *\brief Move the camera depends on the position of the actor. Called by the method act by default.
     */
    
    virtual void moveCamera();

    /**
     *\fn void move(float dt = 0)
     *\brief Move the controlable on the X and Y axis when the keys are pressed and set the new orientation. Called by the method act by default.
     *\param dt Difference time. (Send by the method act)
     */
    
    virtual void move(float dt = 0);

    /**
     *\fn void moveX(float dt = 0)
     *\brief Move the controlable only on the X axis when the keys are pressed and set the new orientation.
     *\param dt Difference time
     */
    
    virtual void moveX(float dt = 0);

    /**
     *\fn void moveY(float dt = 0)
     *\brief Move the controlable only on the Y axis when the keys are pressed and set the new orientation.
     *\param dt Difference time
     */
    
    virtual void moveY(float dt = 0);
  };

  
}  // actor

#endif /* CONTROLABLE_H */
