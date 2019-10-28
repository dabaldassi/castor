#include "menu.h"
#include <iostream>
using ihm::Menu;

void onClickMenu(Element * e, int button)
{
  if(button == 1) {
    Menu<0> * m;
    getDataElement(e, (void **) &m);

    char * name;
    getTextElement(e,&name);
  
    m->shouldCall(name);
  }
}

void onmotion_item(Element * e)
{
  Menu<0> * m;
  getDataElement(e, (void **) &m);
  
  setTextColorElement(e, (int *)m->hover_color());
}

void unmotion_item(Element * e)
{
  Menu<0> * m;
  getDataElement(e, (void **) &m);
  setTextColorElement(e, (int *)m->text_color());
}
