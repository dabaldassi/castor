#include "balle.h"
#include "gameEngine/ihm/color.h"
#include "gameEngine/stage.h"

using actor::Ball;

Ball::Ball(std::string name, Position pos):Moveable(name,1, pos)
{
  loadSprite();
  _speed = 8.f;
  addSound("../sound/hit.wav");
}

void Ball::move(float dt)
{
  // Move the object depending of his orientation
  
  _position.x += _speed * ((_orientation == W || _orientation == NW || _orientation == SW) -
			   (_orientation == E || _orientation == NE || _orientation == SE));
  _position.y += _speed * ((_orientation == N || _orientation == NW || _orientation == NE) -
			   (_orientation == S || _orientation == SE || _orientation == SW));
}

void Ball::act(float dt)
{
  int w,h;

  getDimensionWindow(&w, &h);
  
  move(dt);
  
  if(_position.y < 0 || _position.y > h)
    _stage->endStage();
}

void Ball::effect(Actor * actor)
{

  playSound(0);
  
  if(actor->getName() != "Wall") {
    
    Position pos = actor->getPosition();
    
    _orientation ^= 0x04; // toggle N / W
    
    if(_position.x >= pos.x && _position.x < pos.x + (pos.w/3.f)) {
      _orientation &= 0x04; // Reset E / W
      _orientation |= 0x01; // Set E
    }
    else if(_position.x >= pos.x + (pos.w/3.f) && _position.x < pos.x + (2*pos.w/3.f)) {
      _orientation ^= 0x03;
    }
    else {
      _orientation &= 0x04; // Reset E / W
      _orientation |= 0x02;
    }
  }
  else {
    _orientation ^= 0x03; // Toggle east / west
  }
}

void Ball::loadSprite()
{
  Actor::loadSprite(Color::white);
}
