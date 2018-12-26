/**
 *\file position.h
 *\author dabaldassi
 *\date 07/2018
 */

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <fstream>

typedef enum { N, NE, NW, E, W, SE, SW, S} Orientation;

/**
 *\struct Position
 *\brief Position of an actor
 */

struct Position
{
  float x;
  float y;
  float w;
  float h;
  
  bool use; /* If the position is used by an actor, if the actor has a Position but is not displayed set false */

  Position():use(false){}
  Position(float x, float y):x(x), y(y), w(0), h(0), use(true) {}
  Position(float x, float y, float w, float h):x(x), y(y), w(w), h(h), use(true) {}
  Position(bool u):use(u) {}

  /**
   *\fn bool collide(const Position & p)
   *\brief Tell if another position is colliding with this
   *\return true if it's colliding, else false
   */
  bool collide(const Position & p) const;

  void save(std::ofstream & out);
  void load(std::ifstream & in);
};

Position operator/(const Position & p, float d);

#endif /* POSITION_H */
