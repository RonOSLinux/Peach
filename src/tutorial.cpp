#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"

class HiddenPart {
private:
  int alpha=255;
  Uint32 timer;
  int x;
  int y;
  int w;
  int h;
  int pos=0;
public:
  HiddenPart(int x,int y,int w,int h) {
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
  }
  void setPos(int p) {
    pos=p;
  }
  int getPos() {
    return pos;
  }
  void display() {
    Gui::renderFillRect(x,y,w,h,{5,5,5,(Uint8)alpha});
    if(pos==0) {
      if(SDL_GetTicks()-timer>=25) {
        if(alpha>0) {
          alpha-=5;
        } else {
          alpha=0;
          pos=1;
        }
        timer=SDL_GetTicks();
      }
    } else if(pos==2) {
      if(SDL_GetTicks()-timer>=25) {
        if(alpha<255) {
          alpha+=5;
        } else {
          alpha=255;
          pos=3;
        }
        timer=SDL_GetTicks();
      }
    }
  }
};

class Tutorial: public Gui::Window {
private:
  float wnd_opacity=0.00f;
  Uint32 wnd_blend_t;
  Uint32 state_timer;
  int ani_state=0;
  Gui::Label* welcome_text;
  HiddenPart* welcome_text_hide;

  Gui::Label* skip_text;
  HiddenPart* skip_text_hide;

  Gui::Label* mainpanel_text;
  Gui::Image* mainpanel_img;
  HiddenPart* mainpanel_hide;

  Gui::Label* hotcorners_text;
  Gui::Image* app_img;
  Gui::Image* software_img;
  Gui::Image* restart_img;
  Gui::Image* shutdown_img;
  HiddenPart* hotcorners_hide;

  Gui::Label* thanks_text;
  HiddenPart* thanks_text_hide;
public:
  Tutorial() {
    create("Tutorial",0,0,Gui::dm.w,Gui::dm.h,SDL_WINDOW_SKIP_TASKBAR|SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.00f);

    welcome_text=new Gui::Label("Welcome to RonOS!",Gui::f_light_med,{215,215,215},0,0);
    welcome_text_hide=new HiddenPart(Gui::dm.w/2-400,Gui::dm.h/2-100,800,200);

    skip_text=new Gui::Label("To Skip the Tutorial press Alt+F4!",Gui::f_light_med,{215,215,215},0,0);
    skip_text_hide=new HiddenPart(Gui::dm.w/2-400,Gui::dm.h/2-100,800,200);

    mainpanel_text=new Gui::Label("To Open the Main-Panel move your Mouse down!",Gui::f_light_med,{215,215,215},0,0);
    mainpanel_img=new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/cs-panel.svg"),Gui::dm.w/2-32,Gui::dm.h-74,64,64);
    mainpanel_hide=new HiddenPart(0,0,Gui::dm.w,Gui::dm.h);

    hotcorners_text=new Gui::Label("Move your Mouse into the Corners to Quickstart Apps!",Gui::f_light_med,{215,215,215},0,0);
    app_img=new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/preferences-system-login.svg"),10,10,64,64);
    software_img=new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/software-store.svg"),Gui::dm.w-74,10,64,64);
    restart_img=new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-reboot.svg"),10,Gui::dm.h-74,64,64);
    shutdown_img=new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-shutdown.svg"),Gui::dm.w-74,Gui::dm.h-74,64,64);
    hotcorners_hide=new HiddenPart(0,0,Gui::dm.w,Gui::dm.h);

    thanks_text=new Gui::Label("Thanks for using RonOS!",Gui::f_light_med,{215,215,215},0,0);
    thanks_text_hide=new HiddenPart(Gui::dm.w/2-400,Gui::dm.h/2-100,800,200);

    show();
  }
  virtual void check() {}
  virtual void draw() {
    if(ani_state==0) {
      if(SDL_GetTicks()-wnd_blend_t>=15) {
        if(wnd_opacity<0.70f) {
          wnd_opacity+=0.01f;
          setWindowOpacity(wnd_opacity);
        } else {
          setWindowOpacity(0.70f);
          state_timer=SDL_GetTicks();
          ani_state++;
        }
        wnd_blend_t=SDL_GetTicks();
      }
    } else if(ani_state==1) {
      welcome_text->setX(Gui::dm.w/2-welcome_text->getWidth()/2);
      welcome_text->setY(Gui::dm.h/2-welcome_text->getHeight()/2);
      welcome_text->display();
      welcome_text_hide->display();
      if(SDL_GetTicks()-state_timer>=3500) {
        welcome_text_hide->setPos(2);
        state_timer=SDL_GetTicks();
      }
      if(welcome_text_hide->getPos()==3) {
        state_timer=SDL_GetTicks();
        ani_state++;
      }
    } else if(ani_state==2) {
      skip_text->setX(Gui::dm.w/2-skip_text->getWidth()/2);
      skip_text->setY(Gui::dm.h/2-skip_text->getHeight()/2);
      skip_text->display();
      skip_text_hide->display();
      if(SDL_GetTicks()-state_timer>=3500) {
        skip_text_hide->setPos(2);
        state_timer=SDL_GetTicks();
      }
      if(skip_text_hide->getPos()==3) {
        state_timer=SDL_GetTicks();
        ani_state++;
      }
    } else if(ani_state==3) {
      mainpanel_text->setX(Gui::dm.w/2-mainpanel_text->getWidth()/2);
      mainpanel_text->setY(Gui::dm.h/2-mainpanel_text->getHeight()/2);
      mainpanel_text->display();
      mainpanel_img->display();
      mainpanel_hide->display();
      if(SDL_GetTicks()-state_timer>=5500) {
        mainpanel_hide->setPos(2);
        state_timer=SDL_GetTicks();
      }
      if(mainpanel_hide->getPos()==3) {
        state_timer=SDL_GetTicks();
        ani_state++;
      }
    } else if(ani_state==4) {
      hotcorners_text->setX(Gui::dm.w/2-hotcorners_text->getWidth()/2);
      hotcorners_text->setY(Gui::dm.h/2-hotcorners_text->getHeight()/2);
      hotcorners_text->display();
      app_img->display();
      software_img->display();
      restart_img->display();
      shutdown_img->display();
      hotcorners_hide->display();
      if(SDL_GetTicks()-state_timer>=5500) {
        hotcorners_hide->setPos(2);
        state_timer=SDL_GetTicks();
      }
      if(hotcorners_hide->getPos()==3) {
        state_timer=SDL_GetTicks();
        ani_state++;
      }
    } else if(ani_state==5) {
      thanks_text->setX(Gui::dm.w/2-thanks_text->getWidth()/2);
      thanks_text->setY(Gui::dm.h/2-thanks_text->getHeight()/2);
      thanks_text->display();
      thanks_text_hide->display();
      if(SDL_GetTicks()-state_timer>=3500) {
        thanks_text_hide->setPos(2);
        state_timer=SDL_GetTicks();
      }
      if(thanks_text_hide->getPos()==3) {
        state_timer=SDL_GetTicks();
        ani_state++;
      }
    } else {
      if(SDL_GetTicks()-wnd_blend_t>=15) {
        if(wnd_opacity>0.00f) {
          wnd_opacity-=0.01f;
          setWindowOpacity(wnd_opacity);
        } else {
          setWindowOpacity(0.00f);
          setEnd(true);
        }
        wnd_blend_t=SDL_GetTicks();
      }
    }
  }
};

int main(int argc,char* argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  SDL_GetCurrentDisplayMode(0,&Gui::dm);
  Tutorial tut;
  Gui::quit();
  setModule("tutorial",1);
  return 0;
}
