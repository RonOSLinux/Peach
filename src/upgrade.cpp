#include "../inc/Gui/gui.h"
#include "../inc/SDL_svg.h"
#include "../inc/const.h"
#include "../inc/modules.h"

class Upgrade: public Gui::Window {
private:
  Gui::Label* update_text;
  Gui::Label* upgrade_text;
  Gui::Label* continue_text;
  Gui::Label* warning_text;
  Gui::Label* upgrading_text;
  Gui::Label* updating_text;
  Gui::Label* reboot_text;
  Gui::Label* reboot_now_text;
  Gui::Label* connection_error_text;
  Gui::Label* retry_connection_text;
  Gui::LabelButton* yes_btn;
  Gui::LabelButton* no_btn;
  Gui::ProgressWait* wait;
  bool upgrade_available=false;
  bool call=false;
  int scene=0;
  int t;
public:
  Upgrade() {
    if(getModule("network")==1) {
      if(getCurrentVersion()==getNewVersion()) {
        upgrade_available=false;
      } else {
        upgrade_available=true;
      }
    } else {
      scene=3;
    }
    create("Upgrade",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,870,165,SDL_WINDOW_BORDERLESS,{25,25,25,255});
    setWindowOpacity(0.99f);
    setDragSupport(true);
    update_text=new Gui::Label("There is no Upgrade available, but you can still Update your packages.",Gui::f_light_med,{215,215,215},10,10);
    upgrade_text=new Gui::Label("There is an Upgrade available, the installation will take a while.",Gui::f_light_med,{215,215,215},10,10);
    continue_text=new Gui::Label("Do you want to continue?",Gui::f_reg_med,{215,215,215},10,50);
    reboot_text=new Gui::Label("Important System files has been changed.",Gui::f_light_med,{215,215,215},10,10);
    reboot_now_text=new Gui::Label("Do you want to reboot now?",Gui::f_reg_med,{215,215,215},10,50);
    warning_text=new Gui::Label("(Please don't poweroff the System.)",Gui::f_light_sma,{215,215,215},300,125);
    upgrading_text=new Gui::Label("Upgrading...",Gui::f_reg_med,{215,215,215},35,35);
    updating_text=new Gui::Label("Updating...",Gui::f_reg_med,{215,215,215},35,35);
    connection_error_text=new Gui::Label("Connection Failed! It seems like you aren't connected!",Gui::f_light_med,{215,215,215},10,10);
    retry_connection_text=new Gui::Label("Retry now?",Gui::f_reg_med,{215,215,215},10,50);
    yes_btn=new Gui::LabelButton("Yes",Gui::f_light_med,{215,215,215},120,120);
    no_btn=new Gui::LabelButton("No",Gui::f_light_med,{215,215,215},700,120);
    wait=new Gui::ProgressWait(15,165/2+25,840);
    SDL_SetWindowIcon(Gui::wnd,SDL_LoadSVGFromFile("/usr/share/icons/Papirus/64x64/apps/yast-snapper.svg"));
    show();
  }
  void check() {}
  void draw() {
    if(scene==0) {
      if(upgrade_available) {
        upgrade_text->display();
      } else {
        update_text->display();
      }
      continue_text->display();
      Gui::renderFillRect(0,110,870,95,{28,28,28,255});
      yes_btn->display();
      if(yes_btn->getEvent()==2) {
        scene=1;
      }
      no_btn->display();
      if(no_btn->getEvent()==2) {
        setEnd(true);
      }
    } else if(scene==1) {
      wait->display();
      warning_text->display();
      if(upgrade_available) {
        upgrading_text->display();
        if(!call) {
          setModule("upgrade-action",0);
          t=std::system(("~/"+PEACH_FOLDER+"bin/upgrade-action upgrade &").c_str());
          call=true;
        }
      } else {
        updating_text->display();
        if(!call) {
          setModule("upgrade-action",0);
          t=std::system(("~/"+PEACH_FOLDER+"bin/upgrade-action update &").c_str());
          call=true;
        }
      }
      if(getModule("upgrade-action")==1) {
        setCurrentVersion();
        scene=2;
      }
    } else if(scene==2) {
      reboot_text->display();
      reboot_now_text->display();
      Gui::renderFillRect(0,110,870,95,{28,28,28,255});
      yes_btn->display();
      if(yes_btn->getEvent()==2) {
        setModule("action",2);
        setEnd(true);
      }
      no_btn->display();
      if(no_btn->getEvent()==2) {
        setEnd(true);
      }
    } else if(scene=3) {
      connection_error_text->display();
      retry_connection_text->display();
      Gui::renderFillRect(0,110,870,95,{28,28,28,255});
      yes_btn->display();
      if(yes_btn->getEvent()==2) {
        std::remove(("~/"+PEACH_FOLDER+"sources/upgrade").c_str());
        t=std::system(("wget -O ~/"+PEACH_FOLDER+"sources/upgrade https://raw.githubusercontent.com/RonOSLinux/Peach/master/sources/upgrade").c_str());
        if(getNewVersion()!="") {
          setModule("network",1);
          if(getCurrentVersion()==getNewVersion()) {
            upgrade_available=false;
          } else {
            upgrade_available=true;
          }
          scene=0;
        }
      }
      no_btn->display();
      if(no_btn->getEvent()==2) {
        setEnd(true);
      }
    }
    Gui::renderDrawRect(0,0,870,165,{0,185,255,95});
  }
};

int main(int argc,char const *argv[]) {
  Gui::init();
  Gui::loadFonts("/usr/share/fonts/truetype/Roboto-Regular.ttf","/usr/share/fonts/truetype/Roboto-Light.ttf");
  Gui::normal_color={45,45,45,255};
  Upgrade upgrade;
  Gui::quit();
  setModule("upgrade",0);
  setModule("restart",0);
  setModule("shutdown",0);
  return 0;
}
