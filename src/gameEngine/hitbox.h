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
 *\brief Determine where the object is hit. You use either a position or a shape that you draw yourself with lines
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

  void addLine(LineBox l);
  bool collide(Position& p, int orientation = 0 , float speed = 0);
  void setPosition(Position * p) { _pos = p; }
  void save(std::ofstream & out);
  void load(std::ifstream & in);
  
  virtual ~Hitbox(){}
};


#endif /* HITBOX_H */
