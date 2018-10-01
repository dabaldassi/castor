#include <cmath>

#include "controlable.h"

#include "../../stage.h"

#include "../../ihm/color.h"
#include "../../ihm/keyboard.h"

using actor::Controlable;
using actor::Actor;

Controlable::Controlable(std::string name, Position pos):Character(name, pos)
{
  loadSprite();
  
  _speed = INIT_SPEED_CONTROLABLE;
  _life = 100.f;
  //_position = Position(WIDTH/2.f, HEIGHT/2.f, 100,100);
}

void Controlable::move()
{
  int   o[16] = {_orientation,N,S,_orientation,E,NE,SE,E,W,NW,SW,W,_orientation,N,S,_orientation};
  
  _position.x += _speed * (ihm::Keyboard::keys[RIGHT] - ihm::Keyboard::keys[LEFT]);
  _position.y += _speed * (ihm::Keyboard::keys[FORWARD] - ihm::Keyboard::keys[BACK]);

  //_hitbox.setPosition(_position);

  _orientation = o[(ihm::Keyboard::keys[RIGHT]<<3) + (ihm::Keyboard::keys[LEFT]<<2) + (ihm::Keyboard::keys[BACK]<<1) + ihm::Keyboard::keys[FORWARD]];
}

void Controlable::act(float dt)
{
  /* move de perso */
  
  move();
   
  moveCamera();
  
  /* Search for collision */
  
  searchCollision();
}

void Controlable::searchCollision()
{
  for(auto & a: _stage->actors())
    {
      if(a.get() == this)
	continue;
      else
	if(a.get()->getHitbox().use && a.get()->getHitbox().collide(_position, _orientation, _speed))
	  {
	    a.get()->effect();
	  }
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
      Character::save(out);
      
      out.write((char *)&_speed, sizeof(float));
    }
}

void Controlable::load(std::ifstream &in)
{
  if(in.is_open())
    {
      Character::load(in);
      
      in.read((char *)&_speed, sizeof(float));
    }
}

void Controlable::saveAnnexe(std::ofstream &out)
{}

void Controlable::loadAnnexe(std::ifstream & in)
{}
