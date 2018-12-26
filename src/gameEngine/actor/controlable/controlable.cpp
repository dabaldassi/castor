#include <cmath>

#include "controlable.h"

#include "../../stage.h"

#include "../../ihm/color.h"
#include "../../ihm/keyboard.h"

using actor::Controlable;
using actor::Actor;

int Controlable::_nb_controlable_keyboard = 0;

Controlable::Controlable(const std::string & name, float life, const Position & pos, bool keyboard):Moveable(name,life, pos)
{
  loadSprite();
  
  _speed = INIT_SPEED_CONTROLABLE;
  _nb_controlable_keyboard+=keyboard;
  _keyboard = keyboard;
  _id = _nb_controlable_keyboard;
}

void Controlable::moveX(float dt)
{
  b2Vec2 linearVelocity = _body->GetLinearVelocity();
  
  if(_keyboard) {
    if(_id == 1)
      linearVelocity.x = _speed*(ihm::Keyboard::keys[RIGHT] - ihm::Keyboard::keys[LEFT]);
    else
      linearVelocity.x = _speed*(ihm::Keyboard::keys[RIGHT_2] - ihm::Keyboard::keys[LEFT_2]);

    _orientation = ((ihm::Keyboard::keys[RIGHT] || ihm::Keyboard::keys[RIGHT_2]) ? E : W);
  }

  _body->SetLinearVelocity(linearVelocity);
}

void Controlable::moveY(float dt)
{
  b2Vec2 linearVelocity = _body->GetLinearVelocity();
  
   if(_keyboard) {
    if(_id == 1)
      linearVelocity.y = _speed*(ihm::Keyboard::keys[FORWARD] - ihm::Keyboard::keys[BACK]);
    else
      linearVelocity.y = _speed*(ihm::Keyboard::keys[FORWARD_2] - ihm::Keyboard::keys[BACK_2]);

    _orientation = ((ihm::Keyboard::keys[FORWARD] || ihm::Keyboard::keys[FORWARD_2]) ? N : S);
   }

   _body->SetLinearVelocity(linearVelocity);
}

void Controlable::move(float dt)
{
  int    o[16] = {_orientation,N,S,_orientation,W,NE,SW,W,E,NW,SE,E,_orientation,N,S,_orientation};
  b2Vec2 linearVelocity = _body->GetLinearVelocity();
  
  linearVelocity.x += _speed * (ihm::Keyboard::keys[RIGHT] - ihm::Keyboard::keys[LEFT]);
  linearVelocity.y += _speed * (ihm::Keyboard::keys[FORWARD] - ihm::Keyboard::keys[BACK]);

  _body->SetLinearVelocity(linearVelocity);
  
  _orientation = o[(ihm::Keyboard::keys[RIGHT]<<3) + (ihm::Keyboard::keys[LEFT]<<2) + (ihm::Keyboard::keys[BACK]<<1) + ihm::Keyboard::keys[FORWARD]];
}

void Controlable::act(float dt)
{
  if(_actfct.size() != 0) Actor::act(dt);
  else {
      
    /* move de perso */
    
    move();
    
    moveCamera();
  
  }
}

void Controlable::moveCamera()
{
  float x,y;
  int   w,h;

  getDimensionWindow(&w, &h);
  getCoordElement(_elem, &x, &y);
  _stage->viewport().x += ((x+_position.w/2) - w/2 )*0.001;
  _stage->viewport().y += ( h/2 - (y+_position.h/2))*0.001;
}

void Controlable::loadSprite()
{
  Actor::loadSprite(Color::blue);
}

void Controlable::save(std::ofstream &out)
{
  if(out.is_open())
    {
      Moveable::save(out);
      
      out.write((char *)&_speed, sizeof(float));
    }
}

void Controlable::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Moveable::load(in);
      
      in.read((char *)&_speed, sizeof(float));
    }
}

void Controlable::saveAnnexe(std::ofstream &out)
{}

void Controlable::loadAnnexe(std::ifstream & in)
{}
