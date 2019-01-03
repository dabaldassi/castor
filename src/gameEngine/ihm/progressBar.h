#ifndef CASTOR_PROGRESSBAR_H
#define CASTOR_PROGRESSBAR_H

#include <SANDAL2/SANDAL2.h>
#include "../position.h"

namespace ihm {

  class ProgressBar
  {
  protected:
    Element * _elem;
    float     _width;
    float     _height;
    float     _percent;
    bool      _orientation; /* false : verticaly */
  public:
    ProgressBar():_elem(nullptr){}
    ProgressBar(const Position & pos, int color[4], float percent=0, bool orientation = true);
    
    virtual void set(float percent);
    virtual float get() const { return _percent; }

    void operator=(float percent) { set(percent); }
    
    virtual ~ProgressBar();
  };


}  // ihm

#endif /* PROGRESSBAR_H */
