#include "../inc/Gui/gui.h"
#include "../inc/const.h"
#include <iostream>
#include <string>

class Desktop: public Gui::Window {
private:
  int blend_mode;
  float alpha_state;
  Uint32 blend_timer;
  SDL_DisplayMode dm;
public:
  Desktop() {}
  Desktop(int blend_mode) {
    SDL_GetCurrentDisplayMode(0,&dm);
    create("Desktop",0,0,dm.w,dm.h,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS,{5,5,5,255});
    this->blend_mode=blend_mode;
    if(blend_mode==0) {
      alpha_state=1.0f;
      blend_timer=SDL_GetTicks();
    } else if(blend_mode==1) {
      alpha_state=0.0f;
      blend_timer=SDL_GetTicks();
    }
    add(new Gui::Image(IMG_Load((PEACH_FOLDER+"res/logo.png").c_str()),getWindowSize()[0]/2-64,getWindowSize()[1]/2-64,128,128));
    show();
  }
  void check() {}
  void draw() {
    if(blend_mode==0) {
      if(SDL_GetTicks()-blend_timer>=40) {
        if(alpha_state>0.0f) {
          alpha_state-=0.05f;
          setWindowOpacity(alpha_state);
        } else {
          setEnd(true);
        }
        blend_timer=SDL_GetTicks();
      }
    } else {
      if(SDL_GetTicks()-blend_timer>=40) {
        if(alpha_state<1.0f) {
          alpha_state+=0.05f;
          setWindowOpacity(alpha_state);
        } else {
          setWindowOpacity(1.0f);
        }
        blend_timer=SDL_GetTicks();
      }
    }
  }
};

int main(int argc,char* argv[]) {
  if(argc>1) {
    std::string param;
    param=argv[1];
    Gui::init();
    if(param=="fade-in") {
      Desktop dsk=Desktop(0);
    } else if(param=="fade-out") {
      Desktop dsk=Desktop(1);
    }
    Gui::quit();
  } else {
    std::cout << "Can't start desktop without any params!" << std::endl;
  }
  return 0;
}
