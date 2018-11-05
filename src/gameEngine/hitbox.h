/**
 *\file hitbox.h
 *\author dabaldassi
 *\date 07/2018
 */

#ifndef HITBOX_H
#define HITBOX_H

#include <vector>
#include "position.h"

/**
 *\struct LineBox
 *\brief Line used to draw shape
 */

struct LineBox
{
  Position a;
  Position b;

  LineBox(){}
  LineBox(Position p1, Position p2)  : a(p1), b(p2) {}
};

/**
 *\class Hitbox
 *\brief Determine where the object is hit. You use either a position or a shape that you draw yourself with lines. By default it's in mode position but if you add just one line, it will be in mode shape.
 */

class Hitbox
{
private:
  Position             * _pos;
  std::vector<LineBox>   _shape;
public:
  bool use;
  
  Hitbox():_pos(NULL), use(true) {}
  Hitbox(Position * pos):_pos(pos), use(true) {}

  /**
   *\fn void addLine(LineBox l)
   *\brief If you want to create specific shape, you construct it line by line and add it to the shape with this method.
   *\param l The line which will be added
   */
  
  void addLine(LineBox l);

  /**
   *\fn bool collide(Position& p, int orientation = 0 , float speed = 0)
   *\brief Tell if there is a collision and correct the position not to go go through the other object
   *\param p The position of the object you want to test
   *\param orientation The orientation of the object
   *\param speed The speed of the object
   */
  
  bool collide(Position& p, int orientation = 0 , float speed = 0);

  /**
   *\fn void setPosition(Position * p)
   *\brief Set the position
   *\param p The position
   */
  
  void setPosition(Position * p) { _pos = p; }
  
  void save(std::ofstream & out);
  void load(std::ifstream & in);
  
  virtual ~Hitbox(){}
};


#endif /* HITBOX_H */
