#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/modules.h"

class Restart: public Gui::Window {
private:
public:
  Restart() {
    create("Restart",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,665,135,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS,{245,245,245,255});
    setWindowOpacity(0.99f);
    add(new Gui::Label("Are you sure that you want to restart the system?",Gui::f_reg_med,{75,75,85},31,15));
    add(new Gui::ExitBtn("/usr/share/fonts/truetype/Roboto-Thin.ttf",143,60));
    add(new Gui::Button(470,76,40,40));
    add(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-reboot.svg"),458,64,64,64));
    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-reboot.svg"));
    show();
  }
  void check(){}
  void draw() {
    if(get(1)->getEvent()==2) {
      setEnd(true);
    } else if(get(2)->getEvent()==2) {
      setModule("action",2);
      setEnd(true);
    }
  }
};

int main(int argc,char* argv[]) {
  if(getModule("upgrade")==0) {
    Gui::init();
    Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
    Restart restart;
    Gui::quit();
    setModule("restart",0);
  }
  return 0;
}
