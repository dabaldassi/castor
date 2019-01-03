#include "progressBar.h"

using ihm::ProgressBar;

ProgressBar::ProgressBar(const Position & pos, int color[4], float percent, bool orientation)
{
  int w,h;

  getDimensionWindow(&w, &h);
  
  _elem = createBlock(pos.x - pos.w / 2, h-pos.y, pos.w * percent, pos.h, color, 0,0);

  _width = pos.w;
  _height = pos.h;
  _percent = percent;
  _orientation = orientation;
}

void ProgressBar::set(float percent)
{
  setDimensionElement(_elem, _width * ((_orientation)?percent:1), _height * ((_orientation)?1:percent));

  _percent = percent;
}

ProgressBar::~ProgressBar()
{
  delElement(_elem);
}
