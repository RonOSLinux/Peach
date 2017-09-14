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
    create("Panel",Gui::dm.w/2-161/2,Gui::dm.h/2-368/2,161,268,SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.80f);
    setDragSupport(true);

    old_date=getDate();
    old_time=getTime();
    add(new Gui::Label(old_time.c_str(),Gui::f_reg_big,{225,225,225},40,14));
    add(new Gui::Label(old_date.c_str(),Gui::f_light_med,{195,195,195},8,60));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/32x32/apps/yast.svg"),0,0,32,32),12,224,32,32));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/32x32/apps/internet-web-browser.svg"),0,0,32,32),47,224,32,32));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/32x32/apps/utilities-terminal.svg"),0,0,32,32),82,224,32,32));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/32x32/apps/system-file-manager.svg"),0,0,32,32),117,224,32,32));
    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/cs-panel.svg"));
    show();
  }
  void check() {}
  void draw() {
    Gui::renderFillRect(0,0,161,2,Gui::hover_color);
    Gui::normal_color={10,10,10,255};
    if(getTime()!=old_time) {
      ((Gui::Label*)get(0))->setText(getTime().c_str(),Gui::f_reg_big,{225,225,225});
      old_time=getTime();
    }
    if(getTime()=="00:00") {
      if(getDate()!=old_date) {
        ((Gui::Label*)get(1))->setText(getDate().c_str(),Gui::f_light_med,{195,195,195});
        old_date=getDate();
      }
    }
    if(get(2)->getEvent()==2) {
      if(getModule("settings")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/settings &").c_str());
        setModule("settings",1);
      }
    } else if(get(3)->getEvent()==2) {
      t=std::system("exo-open --launch WebBrowser &");
    } else if(get(4)->getEvent()==2) {
      t=std::system("exo-open --launch TerminalEmulator &");
    } else if(get(5)->getEvent()==2) {
      t=std::system("exo-open --launch FileManager &");
    }
    if(getModule("panel")==2) {
      SDL_RaiseWindow(Gui::wnd);
      setModule("panel",1);
    }
    if(isEnd()) {
      setEnd(false);
    }
  }
};

int main(int argc,char* argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  SDL_GetCurrentDisplayMode(0,&Gui::dm);
  Gui::normal_color={10,10,10,255};
  Gui::hover_color.a=255;
  Panel panel;
  Gui::quit();
  setModule("panel",0);
  return 0;
}
