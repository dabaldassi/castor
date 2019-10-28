#ifndef MENU_H
#define MENU_H

#include <map>
#include <functional>
#include <SANDAL2.h>
#include "font.h"

extern "C" {
  void onClickMenu(Element * e, int button);
  void onmotion_item(Element * e);
  void unmotion_item(Element * e);
}

namespace ihm {

  template<int DISPLAY>
  class Menu
  {
    std::string                                  _title;
    std::string                                  _next_to_call;
    std::map<std::string, std::function<bool()>> _items;
    std::function<void()>                        _gen_background;

    int  _textColor[4], _hoverColor[4];
    bool _run,_shouldCall;
    int  _width, _height;
    
  public:
    Menu():_run(true),_shouldCall(false) {}
    Menu(int width, int height):_run(true),_shouldCall(false),_width(width),_height(height) {}

    using items_t = std::map<std::string, std::function<bool()>>;

    const items_t& items() const { return _items; }
    const int * hover_color() const { return _hoverColor; }
    const int * text_color() const { return _textColor; }
    
    void addItem(const std::string& name, std::function<bool()> fct) { _items[name] = fct; }
    void setBackground(std::function<void()> fct) { _gen_background = fct; }
    void setTextColor(const int textColor[4], const int hoverColor[4]) {
      std::copy(textColor, textColor+4, _textColor);
      std::copy(hoverColor, hoverColor+4, _hoverColor);
    }
    void setTitle(const std::string& title) { _title = title; }

    void shouldCall(const std::string& name) { _shouldCall = true; _next_to_call = name;}
    void run();
    
    virtual ~Menu() {}
  };

  template<int DISPLAY>
  void Menu<DISPLAY>::run() {
    constexpr float textSize = 43.f;
    constexpr float height   = textSize * 1.5f;

    int y = (_height / 2 - height / 2) - _items.size() * height;
    
    _gen_background();

    int width = _title.size() * textSize;
    int x = _width / 2 - width / 2;
    
    createText(x, y, width, height*1.2f, textSize*1.2f, CS_REGULAR, _title.c_str(), _textColor, SANDAL2_BLENDED, DISPLAY,0);

    y += height;
    
    for(auto it : _items) {
      width = it.first.size() * textSize;
      x = _width / 2 - width / 2;
      y += height;
      Element * elem = createText(x, y, width, height, textSize, CS_REGULAR, it.first.c_str(), _textColor, SANDAL2_BLENDED, DISPLAY,0);
      setOnClickElement(elem, onClickMenu);
      addClickableElement(elem, rectangleClickable(0, 0, 1, 1), 0);
      setDataElement(elem, (void *)this);
      setOnMouseMotionElement(elem, onmotion_item);
      setUnMouseMotionElement(elem, unmotion_item);
    }
    
    setDisplayCodeWindow(DISPLAY);
    
    while(_run) {
      _run = !PollEvent(nullptr);
      
      updateWindow();
      displayWindow();
      SDL_Delay(16);

      if(_shouldCall) {
	_run = _items[_next_to_call]();
	_shouldCall = false;
      }
    }

    clearDisplayCode(DISPLAY);
  }
  
}  // ihm



#endif /* MENU_H */
