#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>

std::string getDate() {
  auto t=std::time(nullptr);
  auto tm=*std::localtime(&t);
  std::ostringstream oss;
  oss<<std::put_time(&tm,"%d.%m.%Y");
  auto str=oss.str();
  return str;
}
std::string getTime() {
  auto t=std::time(nullptr);
  auto tm=*std::localtime(&t);
  std::ostringstream oss;
  oss<<std::put_time(&tm,"%H:%M");
  auto str=oss.str();
  return str;
}

class Panel: public Gui::Window {
private:
  std::string old_date;
  std::string old_time;
  int t;
public:
  Panel() {
    create("Panel",Gui::dm.w/2-368/2,Gui::dm.h-161,368,161,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_SKIP_TASKBAR|SDL_WINDOW_BORDERLESS,{15,15,15,255});
    setWindowOpacity(0.98f);
    //Left-Top
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/yast.svg"),0,0,48,48),5,5,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/internet-web-browser.svg"),0,0,48,48),57,5,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/utilities-terminal.svg"),0,0,48,48),5,57,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/system-file-manager.svg"),0,0,48,48),57,57,48,48));
    //Right-Top
    old_date=getDate();
    old_time=getTime();
    add(new Gui::Label(old_time.c_str(),Gui::f_reg_big,{225,225,225},225,16));
    add(new Gui::Label(old_date.c_str(),Gui::f_light_med,{195,195,195},193,58));
    //Bottom
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/preferences-system-login.svg"),0,0,48,48),90,111,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/software-store.svg"),0,0,48,48),138,111,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/system-reboot.svg"),0,0,48,48),186,111,48,48));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/system-shutdown.svg"),0,0,48,48),234,111,48,48));
    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/cs-panel.svg"));
    show();
  }
  void check() {
    if(getEvent().type==SDL_KEYDOWN) {
      if(getEvent().key.keysym.sym==SDLK_ESCAPE) {
        setEnd(true);
      }
    }
  }
  void draw() {
    Gui::renderFillRect(0,0,112,109,{17,17,17,255});
    Gui::renderFillRect(112,0,256,109,{20,20,20,255});
    if(getTime()!=old_time) {
      ((Gui::Label*)get(4))->setText(getTime().c_str(),Gui::f_reg_big,{225,225,225});
      old_time=getTime();
    }
    if(getTime()=="00:00") {
      if(getDate()!=old_date) {
        ((Gui::Label*)get(5))->setText(getDate().c_str(),Gui::f_light_med,{195,195,195});
        old_date=getDate();
      }
    }
    if(get(0)->getEvent()==2) {
      if(getModule("settings")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/settings &").c_str());
        setModule("settings",1);
      }
    } else if(get(1)->getEvent()==2) {
      t=std::system("exo-open --launch WebBrowser &");
    } else if(get(2)->getEvent()==2) {
      t=std::system("exo-open --launch TerminalEmulator &");
    } else if(get(3)->getEvent()==2) {
      t=std::system("exo-open --launch FileManager &");
    } else if(get(6)->getEvent()==2) {
      if(getModule("apps")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/apps &").c_str());
        setModule("apps",1);
      }
    } else if(get(7)->getEvent()==2) {
      if(getModule("software")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/software-explorer &").c_str());
        setModule("software",1);
      }
    } else if(get(8)->getEvent()==2) {
      if(getModule("restart")!=1&&getModule("shutdown")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/restart &").c_str());
        setModule("restart",1);
      }
    } else if(get(9)->getEvent()==2) {
      if(getModule("shutdown")!=1&&getModule("restart")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/shutdown &").c_str());
        setModule("shutdown",1);
      }
    }
  }
};

int main(int argc,char* argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  SDL_GetCurrentDisplayMode(0,&Gui::dm);
  Gui::prefer_global_mouse=true;
  Panel panel;
  Gui::quit();
  setModule("panel",0);
  return 0;
}
