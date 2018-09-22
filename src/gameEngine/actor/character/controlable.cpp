#include <cmath>

#include "controlable.h"

#include "../../screen.h"
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
  _position = Position(WIDTH/2.f, HEIGHT/2.f, 100,100);
}

void Controlable::act(float dt)
{
  int   o[16] = {_orientation,N,S,_orientation,E,NE,SE,E,W,NW,SW,W,_orientation,N,S,_orientation};

 
  /* move de perso */
  
  _position.x += _speed * (Keyboard::keys[RIGHT] - Keyboard::keys[LEFT]);
  _position.y += _speed * (Keyboard::keys[FORWARD] - Keyboard::keys[BACK]);

  _hitbox.setPosition(_position);

  _orientation = o[(Keyboard::keys[RIGHT]<<3) + (Keyboard::keys[LEFT]<<2) + (Keyboard::keys[BACK]<<1) + Keyboard::keys[FORWARD]];
   
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

  getCoordElement(_elem, &x, &y);
  _stage->viewport().x += ((x+_position.w/2) - WIDTH/2 )*0.1;
  _stage->viewport().y += ( HEIGHT/2 - (y+_position.h/2))*0.1;
}

void Controlable::loadSprite()
{
  _elem = createBlock(_position.x - (_position.w/2), _position.y - _position.h/2, 100, 100, Color::blue, GAME, 0);
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
