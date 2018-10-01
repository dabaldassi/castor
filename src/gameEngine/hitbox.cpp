#include <cmath>
#include <iostream>

#include "hitbox.h"

/**
 *\fn void correctPosition(Position & _position, int orientation, float speed,const Position & posObj, float b)
 *\brief Put a position at the edge of collidign with the other
 *\param _position The position to correct
 *\param posOBj Position the the object that causes a collision
 *\param b If there was an linear interpolation, absolute difference of the two orgigin ordinate
 */

void correctPosition(Position & _position, int orientation, float speed,const Position & posObj, float b)
{
  Position p;
  p.x = _position.x;
  p.y = _position.y;
  
  switch(orientation)
    {
    case N:
      _position.y += (posObj.use)?(posObj.y - posObj.h) - _position.y:-b;
      break;
    case S:
      _position.y += (posObj.use)?posObj.y - (_position.y - _position.h):b;
      break;
    case E:
      _position.x += (posObj.use)?(posObj.x + posObj.w) - _position.x:b;
      break;
    case W:
      _position.x += (posObj.use)?posObj.x - (_position.w + _position.x):-b;
      break;
    case NE:
      _position.y += (posObj.use)?(posObj.y - posObj.h) - _position.y:-b/2;
      _position.x += (posObj.use)?(posObj.x + posObj.w) - _position.x:b/2;
      break;
    case NW:
      _position.y += (posObj.use)?(posObj.y - posObj.h) - _position.y:-b/2;
      _position.x += (posObj.use)?posObj.x - (_position.w + _position.x):-b/2;
      break;
    case SW:
      _position.y += (posObj.use)?posObj.y - (_position.y - _position.h):b/2;
      _position.x += (posObj.use)?posObj.x - (_position.w + _position.x):-b/2;
      break;
    case SE:
      _position.y += (posObj.use)?posObj.y - (_position.y - _position.h):b/2;
      _position.x += (posObj.use)?(posObj.x + posObj.w) - _position.x:b/2;
      break;
    }

  if(posObj.use)
    {
      if(abs(p.x - _position.x) > speed)
	_position.x = p.x;

      if(abs(p.y - _position.y) > speed)
	_position.y = p.y;
    }
}

void correctPosition(Position & _position, int orientation, float speed,const Position & posObj)
{
  correctPosition(_position, orientation, speed, posObj, 0);
}

void correctPosition(Position & _position, int orientation, float speed,float b)
{
  correctPosition(_position, orientation, speed, Position(false), b);
}

bool Hitbox::collide(Position& p, int orientation, float speed)
{
  bool collision = false;
  
  if(_pos && _pos->use)
    {
      collision = _pos->collide(p);
      if(speed != 0 && collision)
	correctPosition(p, orientation, speed, *_pos);
    }
  else
    {
      /* Check if there is a collision with any line of the shape*/
      for(LineBox l:_shape)
	{
	  if(l.a.x == l.b.x) /* if they have the same abscisse */
	    {
	      /* Create a position at this point and check for collision */
	      Position pos = Position(l.a.x, fmaxf(l.a.y, l.b.y), 1,fabsf(l.a.y - l.b.y));
	      collision = p.collide(pos);
	      
	      if(collision && speed != 0)
		correctPosition(p, orientation, speed, pos);
	    }
	  else if(l.a.y == l.b.y) /* Idem if they have the same ordinate */
	    {
	      Position pos = Position(fminf(l.a.x, l.b.x),l.a.y, fabsf(l.a.x - l.b.x), 1);
	      collision = p.collide(pos);
	      
	      if(collision && speed != 0)
		correctPosition(p, orientation, speed, pos);
	    }
	  else
	    {
	      /* Linear interpolation */
	      float a = (l.b.y - l.a.y) / (l.b.x - l.a.x); /* Straight line coeficient */
	      float b = l.a.y - l.a.x * a; /* Ordinate origin */

	      /* Calculation of the origin ordinate of the four points of the position on the same coefficient*/
	      
	      float b1 = p.y - p.x * a;
	      float b2 = p.y - (p.x + p.w) * a;
	      float b3 = (p.y - p.h) - p.x * a;
	      float b4 = (p.y - p.h) - (p.x + p.w) * a;

	      /* Determination of collision */
	      
	      if(a > 0 && p.y - p.h < l.b.y && p.y > l.a.y && p.x + p.w > l.a.x && p.x < l.b.x)
		{
		  if(b4 < b && b1 > b && b2 > b) /* Fourth point */
		    correctPosition(p, orientation, speed, fminf(2*speed,fabs(b-b4)));
		  else if(b1 > b && b4 < b && b2 < b) /* First point */
		    correctPosition(p, orientation, speed, fminf(2*speed,fabsf(b-b1)));
		  else
		    collision = !collision;
		}
	      else if(a < 0 && p.y - p.h < l.a.y && p.y > l.b.y && p.x + p.w > l.a.x && p.x < l.b.x)
		{
		  if(b2 > b && b3 < b && b1 < b)
		    correctPosition(p, orientation, speed, fminf(2*speed,fabsf(b-b2))); /* Second point */
		  else if(b3 < b && b2 > b && b1 > b)
		    correctPosition(p, orientation, speed, fminf(2*speed,fabsf(b-b3))); /*Third point */
		  else
		    collision = !collision;
		}
	      else
		collision = !collision;

	      collision = !collision;
	    }

	  if(collision) break;
	}
    }

  return collision;
}

void Hitbox::addLine(LineBox l) 
{
  _shape.push_back(l);

  if(_pos && _pos->use)
    _pos->use = false;
}

void Hitbox::save(std::ofstream &out)
{
  int length = _shape.size();

  if(out.is_open())
    {
      out.write((char *)&use, sizeof(bool));
      out.write((char *)&length, sizeof(int));
  
      if(length == 0)
	{
	  _pos->save(out);
	}
      else
	{
	  for(LineBox l : _shape)
	    {
	      l.a.save(out);
	      l.b.save(out);
	    }
	}
    }
}

void Hitbox::load(std::ifstream &in)
{
  int length;

  if(in.is_open())
    {
      in.read((char *)&use, sizeof(bool));
      in.read((char *)&length, sizeof(int));

      if(length == 0)
	_pos->load(in);
      else
	{
	  for(int i=0; i<length; i++)
	    {
	      LineBox l;

	      l.a.load(in);
	      l.b.load(in);

	      addLine(l);
	    }
	}
    }
}
