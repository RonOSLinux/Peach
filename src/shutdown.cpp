#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/modules.h"

class Shutdown: public Gui::Window {
private:
public:
  Shutdown() {
    create("Shutdown",Gui::dm.w/2-665/2,Gui::dm.h/2-135/2,665,135,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.95f);
    add(new Gui::Label("Are you sure that you want to shutdown the system?",Gui::f_light_med,{215,215,215},11,15));
    add(new Gui::ExitBtn("/usr/share/fonts/truetype/Roboto-Thin.ttf",143,60));
    add(new Gui::Button(470,76,40,40));
    add(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-shutdown.svg"),458,64,64,64));
    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/system-shutdown.svg"));
    show();
  }
  void check(){}
  void draw() {
    Gui::renderFillRect(0,0,665,2,Gui::hover_color);
    if(get(1)->getEvent()==2) {
      setEnd(true);
    } else if(get(2)->getEvent()==2) {
      setModule("action",1);
      setEnd(true);
    }
  }
};

int main(int argc,char* argv[]) {
  if(getModule("upgrade")==0) {
    Gui::init();
    Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
    Gui::hover_color.a=255;
    Gui::prefer_global_mouse=true;
    SDL_GetCurrentDisplayMode(0,&Gui::dm);
    Shutdown shutdown;
    Gui::quit();
    setModule("shutdown",0);
  }
  return 0;
}
