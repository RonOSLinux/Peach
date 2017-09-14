#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"
#include "../inc/AppFolder.h"
#include "../inc/Ini.h"

class Software: public Gui::Window {
private:
  int active_cat=-1;
  int active_app=-1;
  bool app_installed=false;
  bool process=false;
  AppFolder appf;
  Gui::Label* no_cat;
  Gui::Label* no_app;
  std::array<Gui::Label*,10> cat_labels;
  std::vector<Gui::Button*> app_btns;
  std::vector<Gui::Tooltip*> app_tips;
  Gui::Image* app_img;
  Gui::Label* app_name;
  Gui::Label* app_desc;
  Gui::Button* app_action_inst;
  Gui::Button* app_action_del;
  Gui::Label* installing;
  Gui::Label* removing;
  Gui::ProgressBar* bar;
  int t;
public:
  Software() {
    create("SoftwareExplorer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,538,469,SDL_WINDOW_BORDERLESS,{5,5,5,255});
    setWindowOpacity(0.9f);
    setDragSupport(true);
    appf.init();
    sources::init();
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

    no_cat=new Gui::Label("Please choose a Category from above!",Gui::f_light_med,{215,215,215},34,205);
    no_app=new Gui::Label("Please choose an App from above!",Gui::f_light_med,{215,215,215},58,418);
    for(int i=0;i<10;i++) {
      cat_labels[i]=new Gui::Label(appf.getShownNames()[i].c_str(),Gui::f_light_med,{205,205,205},10,63);
    }
    for(int i=0;i<sources::apps.size();i++) {
      SDL_Surface* tmp_sur=SDL_LoadSVGFromFile(("/usr/share/icons/Papirus/48x48/apps/"+sources::icon.at(i)+".svg").c_str());
      app_btns.push_back(new Gui::Button(new Gui::Image(tmp_sur,0,0,48,48),0,0,48,48));
      app_tips.push_back(new Gui::Tooltip(app_btns.at(i),sources::apps.at(i).c_str(),0));
    }

    app_img=new Gui::Image((SDL_Texture*)NULL,5,400,64,64);
    app_name=new Gui::Label("",Gui::f_light_med,{185,185,185},74,406);
    app_desc=new Gui::Label("",Gui::f_light_sma,{215,215,215},74,435);
    app_action_inst=new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/apps/kget.svg"),0,0,48,48),477,408,48,48);
    app_action_del=new Gui::Button(new Gui::Image(SDL_LoadSVGFromFile("/usr/share/icons/Papirus/48x48/emblems/emblem-unreadable.svg"),0,0,48,48),477,408,48,48);

    installing=new Gui::Label("Installing...",Gui::f_light_med,{215,215,215},20,72);
    removing=new Gui::Label("Removing...",Gui::f_light_med,{215,215,215},20,72);
    bar=new Gui::ProgressBar(538/2-450/2,469/2-3/2,450);

    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/software-store.svg"));
    show();
  }
  void check() {}
  void draw() {
    Gui::renderFillRect(0,0,538,2,{0,185,235,255});
    if(!process) {
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
        for(int i=0;i<sources::apps.size();i++) {
          if(active_cat==sources::categorie.at(i)) {
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
              app_img->setIMG(SDL_LoadSVGFromFile(("/usr/share/icons/Papirus/64x64/apps/"+sources::icon.at(i)+".svg").c_str()));
              app_name->setX(74);
              app_name->setY(406);
              app_name->setText((sources::apps.at(i)).c_str(),Gui::f_light_med,{155,155,155});
              app_desc->setText((sources::description.at(i)).c_str(),Gui::f_light_sma,{185,185,185});
              active_app=i;
              app_installed=false;
              for(int i=0;i<appf.getAvailableApps().size();i++) {
                if(appf.getRealName(appf.getAvailableApps().at(i))==sources::apps.at(active_app)) {
                  app_installed=true;
                  break;
                }
              }
            }
            app_tips.at(i)->update();
            app_tips.at(i)->display();
          }
        }
      }
      Gui::renderFillRect(5,400,528,64,{15,15,15,195});
      if(active_cat!=-1) {
        if(active_app==-1) {
          no_app->display();
        } else {
          Gui::normal_color={15,15,15,195};
          Gui::hover_color={35,35,35,255};
          app_img->display();
          app_name->setX(74);
          app_name->setY(406);
          app_name->display();
          app_desc->display();
          if(!app_installed) {
            app_action_inst->display();
            if(app_action_inst->getEvent()==2) {
              setModule("software-action",0);
              t=std::system(("~/"+PEACH_FOLDER+"bin/software-action install "+sources::install.at(active_app)+" &").c_str());
              process=true;
            }
          } else {
            app_action_del->display();
            if(app_action_del->getEvent()==2) {
              setModule("software-action",0);
              t=std::system(("~/"+PEACH_FOLDER+"bin/software-action remove "+sources::install.at(active_app)+" &").c_str());
              process=true;
            }
          }
        }
      }
      Gui::normal_color={15,15,15,195};
      Gui::hover_color={35,35,35,255};
    } else {
      Gui::normal_color={35,35,35,195};
      Gui::hover_color={0,185,235,255};
      for(int i=0;i<10;i++) {
        ((Gui::CheckButton*)get(i+1))->setActive(false);
      }
      Gui::renderFillRect(5,58,528,406,{15,15,15,195});
      if(!app_installed) {
        installing->display();
        app_name->setX(538/2-app_name->getWidth()/2);
        app_name->setY(469/2-app_name->getHeight()/2-50);
        app_name->display();
      } else {
        removing->display();
        app_name->setX(538/2-app_name->getWidth()/2);
        app_name->setY(469/2-app_name->getHeight()/2-50);
        app_name->display();
      }
      bar->display();
      if(getModule("software-action")==1) {
        process=false;
        appf.clearAll();
        appf.init();
        active_cat=-1;
        active_app=-1;
        bar->setPos(0.0);
      }
    }
  }
};

int main(int argc,char* argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  Gui::normal_color={15,15,15,195};
  Gui::hover_color={35,35,35,255};
  Software software;
  Gui::quit();
  setModule("software",0);
  return 0;
}
