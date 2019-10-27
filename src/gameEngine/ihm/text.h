#ifndef TEXT_H
#define TEXT_H

#include "SANDAL2.h"

namespace ihm {

  class Text
  {
  public:
    Text();

    static Element * create(float x, float y, float width, float height, float, const char *font, const char *text, int *textColor, int quality, int displayCode, int plan);
  
    virtual ~Text();
  };

}  // ihm

#endif /* TEXT_H */
