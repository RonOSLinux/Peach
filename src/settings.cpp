#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"

class Settings: public Gui::Window {
private:
  int t;
public:
  Settings() {
    create("Settings",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,161,268,SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.95f);
    setDragSupport(true);

    add(new Gui::ExitBtn("/usr/share/fonts/truetype/Roboto-Thin.ttf",120,-10));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/utilities-tweak-tool.svg"),0,0,64,64),161/2-32,50,64,64));
    add(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/yast-snapper.svg"),0,0,64,64),161/2-32,140,64,64));
    add(new Gui::Label("Settings",Gui::f_light_sma,{215,215,215},47,115));
    add(new Gui::Label("Upgrade",Gui::f_light_sma,{215,215,215},46,205));

    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/yast.svg"));

    show();
  }
  void check() {}
  void draw() {
    if(get(0)->getEvent()==2) {
      setEnd(true);
    }
    if(get(1)->getEvent()==2) {
      t=std::system("xfce4-settings-manager &");
      setEnd(true);
    }
    if(get(2)->getEvent()==2) {
      if(getModule("upgrade")!=1) {
        t=std::system(("~/"+PEACH_FOLDER+"bin/upgrade &").c_str());
        setModule("upgrade",1);
      }
      setEnd(true);
    }
  }
};

int main(int argc,char const *argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  Gui::normal_color={5,5,5,255};
  Gui::hover_color.a=255;
  Settings settings;
  Gui::quit();
  setModule("settings",0);
  return 0;
}
