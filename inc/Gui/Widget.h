#ifndef _Widget
#define _Widget

class Widget {
private:
  int x;
  int y;
  int w;
  int h;
  int event;
  bool state;
public:
  Widget() {
    x=0;
    y=0;
    w=0;
    h=0;
    event=0;
    state=true;
  }
  ~Widget() {}
  void create(int x,int y,int w,int h) {
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
  }
  void checkEvent() {
    if(state) {
      if(!prefer_global_mouse) {
        if(mousex>x&&mousex<x+w&&mousey>y&&mousey<y+h&&SDL_MOUSEBUTTONDOWN&&SDL_BUTTON(SDL_GetMouseState(&mousex,&mousey))==SDL_BUTTON_LEFT&&SDL_GetTicks()-mousetimer>=180) {
          event=2;
          mousetimer=SDL_GetTicks();
        } else if(mousex>x&&mousex<x+w&&mousey>y&&mousey<y+h) {
          event=1;
        } else {
          event=0;
        }
      } else {
        if(gmousex>x+wnd_x&&gmousex<x+wnd_x+w&&gmousey>y+wnd_y&&gmousey<y+wnd_y+h&&SDL_MOUSEBUTTONDOWN&&SDL_BUTTON(SDL_GetGlobalMouseState(&gmousex,&gmousey))==SDL_BUTTON_LEFT&&SDL_GetTicks()-mousetimer>=180) {
          event=2;
          mousetimer=SDL_GetTicks();
        } else if(gmousex>x+wnd_x&&gmousex<x+wnd_x+w&&gmousey>y+wnd_y&&gmousey<y+wnd_y+h) {
          event=1;
        } else {
          event=0;
        }
      }
    } else {
      event=0;
    }
  }
  virtual void display()=0;

  //set-methods
  void setX(int v) {
    x=v;
  }
  void setY(int v) {
    y=v;
  }
  void setWidth(int v) {
    w=v;
  }
  void setHeight(int v) {
    h=v;
  }
  void setState(bool x) {
    state=x;
  }

  //get-methods
  int getEvent() {
    return event;
  }
  int getX() {
    return x;
  }
  int getY() {
    return y;
  }
  int getWidth() {
    return w;
  }
  int getHeight() {
    return h;
  }
  bool getState() {
    return state;
  }
};

#endif
