#include "position.h"

bool Position::collide(const Position & p) const
{
  return (p.x + p.w >= x && p.x <= x + w) && (p.y + p.h >= y && p.y <= y + h);
}

void Position::save(std::ofstream &out)
{
  if(out.is_open())
    {
      out.write((char *)&x, sizeof(float));
      out.write((char *)&y, sizeof(float));
      out.write((char *)&w, sizeof(float));
      out.write((char *)&h, sizeof(float));
      out.write((char *)&use, sizeof(bool));
    }
}

void Position::load(std::ifstream &in)
{
  if(in.is_open())
    {
      in.read((char *)&x, sizeof(float));
      in.read((char *)&y, sizeof(float));
      in.read((char *)&w, sizeof(float));
      in.read((char *)&h, sizeof(float));
      in.read((char *)&use, sizeof(bool));
    }
}
