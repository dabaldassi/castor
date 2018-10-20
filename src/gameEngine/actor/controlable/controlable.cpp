#include <cmath>

#include "controlable.h"

#include "../../stage.h"

#include "../../ihm/color.h"
#include "../../ihm/keyboard.h"

using actor::Controlable;
using actor::Actor;

int Controlable::_nb_controlable_keyboard = 0;

Controlable::Controlable(std::string name, float life, Position pos, bool keyboard):Moveable(name,life, pos)
{
  loadSprite();
  
  _speed = INIT_SPEED_CONTROLABLE;
  _nb_controlable_keyboard+=keyboard;
  _keyboard = keyboard;
  _id = _nb_controlable_keyboard;
}

void Controlable::moveX(float dt)
{
  if(_keyboard) {
    if(_id == 1)
      _position.x += _speed*(ihm::Keyboard::keys[RIGHT] - ihm::Keyboard::keys[LEFT]);
    else
      _position.x += _speed*(ihm::Keyboard::keys[RIGHT_2] - ihm::Keyboard::keys[LEFT_2]);

    _orientation = ((ihm::Keyboard::keys[RIGHT] || ihm::Keyboard::keys[RIGHT_2]) ? E : W);
  }
}

void Controlable::moveY(float dt)
{
   if(_keyboard) {
    if(_id == 1)
      _position.y += _speed*(ihm::Keyboard::keys[FORWARD] - ihm::Keyboard::keys[BACK]);
    else
      _position.y += _speed*(ihm::Keyboard::keys[FORWARD_2] - ihm::Keyboard::keys[BACK_2]);

    _orientation = ((ihm::Keyboard::keys[FORWARD] || ihm::Keyboard::keys[FORWARD_2]) ? N : S);
   }
}

void Controlable::move(float dt)
{
  int   o[16] = {_orientation,N,S,_orientation,W,NE,SW,W,E,NW,SE,E,_orientation,N,S,_orientation};
  
  _position.x += _speed * (ihm::Keyboard::keys[RIGHT] - ihm::Keyboard::keys[LEFT]);
  _position.y += _speed * (ihm::Keyboard::keys[FORWARD] - ihm::Keyboard::keys[BACK]);
  
  _orientation = o[(ihm::Keyboard::keys[RIGHT]<<3) + (ihm::Keyboard::keys[LEFT]<<2) + (ihm::Keyboard::keys[BACK]<<1) + ihm::Keyboard::keys[FORWARD]];
}

void Controlable::act(float dt)
{
  if(_actfct.size() != 0) Actor::act(dt);
  else {
      
    /* move de perso */
    
    move();
    
    moveCamera();
  
    /* Search for collision */
  
    searchCollision();
  }
}

void Controlable::moveCamera()
{
  float x,y;
  int   w,h;

  getDimensionWindow(&w, &h);
  getCoordElement(_elem, &x, &y);
  _stage->viewport().x += ((x+_position.w/2) - w/2 )*0.1;
  _stage->viewport().y += ( h/2 - (y+_position.h/2))*0.1;
}

void Controlable::loadSprite()
{
  _elem = createBlock(_position.x - (_position.w/2), _position.y - _position.h/2, 100, 100, Color::blue, 0, 0);
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
