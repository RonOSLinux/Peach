#ifndef _Window
#define _Window

class Window {
private:
  SDL_Event e;
  SDL_Color bg_color;
  bool end;
  int wnd_width;
  int wnd_height;
  float opacity;
  bool drag;
  bool drag_start;
  int rmousex;
  int rmousey;
  std::vector<Widget*> widgets;
public:
  Window() {
    end=false;
    wnd_width=0;
    wnd_height=0;
    bg_color={0,0,0,255};
    opacity=1.0f;
    drag=false;
    drag_start=false;
    rmousex=0;
    rmousey=0;
  }
  ~Window() {}
  void create(const char* title,int x,int y,int w,int h,int state,SDL_Color bg) {
    wnd=SDL_CreateWindow(title,x,y,w,h,state);
    ren=SDL_CreateRenderer(wnd,0,-1);
    SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    bg_color=bg;
    wnd_x=x;
    wnd_y=y;
    wnd_width=w;
    wnd_height=h;
    end=false;
  }
  virtual void check()=0;
  virtual void draw()=0;
  virtual void event() {
    while(SDL_PollEvent(&e)) {
      if(e.type==SDL_QUIT) {
        end=true;
      } else {
        check();
      }
    }
  }
  void show() {
    do {
      event();
      SDL_GetMouseState(&mousex,&mousey);
      if(drag||prefer_global_mouse) {
        SDL_GetGlobalMouseState(&gmousex,&gmousey);
      }
      SDL_SetWindowOpacity(wnd,opacity);
      SDL_RenderClear(ren);
      renderFillRect(0,0,wnd_width,wnd_height,bg_color);
      draw();
      for(Widget* t: widgets) {
        t->display();
      }
      if(drag) {
        if(SDL_MOUSEBUTTONDOWN&&SDL_BUTTON(SDL_GetMouseState(&mousex,&mousey))==SDL_BUTTON_LEFT) {
          if(!drag_start) {
            rmousex=mousex;
            rmousey=mousey;
            drag_start=true;
          }
          SDL_SetWindowPosition(wnd,gmousex-rmousex,gmousey-rmousey);
          wnd_x=gmousex-rmousex;
          wnd_y=gmousey-rmousey;
        } else {
          drag_start=false;
        }
      }
      SDL_RenderPresent(ren);
      SDL_Delay(15);
    } while(!end);
  }
  void add(Widget* w) {
    widgets.push_back(w);
  }
  Widget* get(int i) {
    return widgets.at(i);
  }
  //set-methods
  void setEnd(bool x) {
    end=x;
  }
  void setWindowSize(int w,int h) {
    wnd_width=w;
    wnd_height=h;
    SDL_SetWindowSize(wnd,wnd_width,wnd_height);
  }
  void setWindowOpacity(float x) {
    if(x<=1.0f) {
      opacity=x;
    }
  }
  void setDragSupport(bool x) {
    drag=x;
  }

  //get-methods
  bool isEnd() {
    return end;
  }
  int* getWindowSize() {
    int* r=new int[2];
    r[0]=wnd_width;
    r[1]=wnd_height;
    return r;
  }
  float getWindowOpacity() {
    return opacity;
  }
  bool getDragSupport() {
    return drag;
  }
  SDL_Event getEvent() {
    return e;
  }
};

#endif
