#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
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
    add(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/tux.svg"),getWindowSize()[0]/2-32,getWindowSize()[1]/2-32,64,64));
    add(new Gui::Label("RonOS",Gui::f_light_big,{125,125,125},0,0));
    show();
  }
  void check() {}
  void draw() {
    get(1)->setX(getWindowSize()[0]/2-get(1)->getWidth()/2);
    get(1)->setY(getWindowSize()[1]/2-get(1)->getHeight()/2+64);
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
    Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Thin.ttf");
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
