#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"
#include "../inc/AppFolder.h"

class Apps: public Gui::Window {
private:
  int active_cat=-1;
  AppFolder appf;
  Gui::Label* no_cat;
  std::array<Gui::Label*, 10> cat_labels;
  std::vector<Gui::Button*> app_btns;
  std::vector<Gui::Tooltip*> app_tips;
  int t;
public:
  Apps() {
    create("Apps",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,538,400,SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.95f);
    setDragSupport(true);

    add(new Gui::ExitBtn("/usr/share/fonts/truetype/Roboto-Thin.ttf",493,-7));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/multimedia-video-player.svg"),0,0,48,48),5,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-development.svg"),0,0,48,48),53,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-education.svg"),0,0,48,48),101,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-games.svg"),0,0,48,48),149,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-graphics.svg"),0,0,48,48),197,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-internet.svg"),0,0,48,48),245,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-office.svg"),0,0,48,48),293,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-science.svg"),0,0,48,48),341,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-system.svg"),0,0,48,48),389,5,48,48));
    add(new Gui::CheckButton(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-accessories.svg"),0,0,48,48),437,5,48,48));

    appf.init();

    no_cat=new Gui::Label("Please choose a Category from above!",Gui::f_light_med,{215,215,215},34,200);
    for(int i=0;i<10;i++) {
      cat_labels[i]=new Gui::Label(appf.getShownNames()[i].c_str(),Gui::f_light_med,{205,205,205},10,63);
    }
    for(int i=0;i<appf.getAvailableApps().size();i++) {
      SDL_Surface* tmp_sur=SDL_LoadSVGFromFile(("/usr/share/icons/Papirus/48x48/apps/"+appf.getIconName(appf.getAvailableApps().at(i))).c_str());
      if(tmp_sur!=NULL) {
        app_btns.push_back(new Gui::Button(new Gui::Image(tmp_sur,0,0,48,48),0,0,48,48));
      } else {
        app_btns.push_back(new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/applications-system.svg"),0,0,48,48),0,0,48,48));
      }
      app_tips.push_back(new Gui::Tooltip(app_btns.at(i),appf.getRealName(appf.getAvailableApps().at(i)).c_str(),0));
    }

    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/preferences-system-login.svg"));
    show();
  }
  void check() {}
  void draw() {
    if(get(0)->getEvent()==2) {
      setEnd(true);
    }
    bool t=false;
    for(int i=0;i<10;i++) {
      if(get(i+1)->getEvent()==2&&((Gui::CheckButton*)get(i+1))->getActive()==true) {
        active_cat=i;
        t=true;
      } else if(get(i+1)->getEvent()==2&&((Gui::CheckButton*)get(i+1))->getActive()==false) {
        active_cat=-1;
      } else if(i==active_cat) {
        t=true;
      } else {
        ((Gui::CheckButton*)get(i+1))->setActive(false);
      }
    }
    if(!t) {
      active_cat=-1;
    }
    Gui::renderFillRect(5,58,528,337,{15,15,15,195});
    Gui::renderFillRect(485,5,48,48,{15,15,15,195});
    if(active_cat==-1) {
      no_cat->display();
    } else {
      cat_labels[active_cat]->display();
      int x=0;
      int y=0;
      for(int i=0;i<appf.getAvailableApps().size();i++) {
        if(appf.getAvailableCats().at(i)==appf.getShownNames()[active_cat]) {
          app_btns.at(i)->setX(5+x);
          app_btns.at(i)->setY(100+y);
          x+=48;
          if(x>=6*48) {
            app_tips.at(i)->setPosMode(1);
          } else {
            app_tips.at(i)->setPosMode(0);
          }
          if(x==11*48) {
            x=0;
            y+=48;
          }
          app_btns.at(i)->display();
          if(app_btns.at(i)->getEvent()==2) {
            t=std::system((appf.getExecPath(appf.getAvailableApps().at(i))+" &").c_str());
            setEnd(true);
          }
          app_tips.at(i)->update();
          app_tips.at(i)->display();
        }
      }
    }
  }
};

int main(int argc,char* argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  Gui::normal_color={15,15,15,195};
  Gui::hover_color={35,35,35,255};
  Apps apps;
  Gui::quit();
  setModule("apps",0);
  return 0;
}
