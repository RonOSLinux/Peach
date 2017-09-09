#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include "../inc/const.h"
#include "../inc/modules.h"

int main(int argc,char* argv[]) {
    int t;
    int mx;
    int my;
    bool end=false;
    SDL_DisplayMode dm;
    SDL_Event e;

    resetAllModules();

    //Update Current Version
    std::remove(("~/"+PEACH_FOLDER+"sources/upgrade").c_str());
    t=std::system(("wget -O ~/"+PEACH_FOLDER+"sources/upgrade https://raw.githubusercontent.com/RonOSLinux/Peach/master/sources/upgrade").c_str());

    t=std::system(("~/"+PEACH_FOLDER+"bin/desktop fade-in").c_str());
    if(getModule("tutorial")==0) {
      t=std::system(("~/"+PEACH_FOLDER+"bin/tutorial").c_str());
    }
    t=std::system(("~/"+PEACH_FOLDER+"bin/panel &").c_str());
    setModule("panel",1);
    if(getCurrentVersion()!=getNewVersion()) {
      t=std::system(("~/"+PEACH_FOLDER+"bin/upgrade &").c_str());
      setModule("upgrade",1);
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GetCurrentDisplayMode(0,&dm);

    while(!end) {
      SDL_PollEvent(&e);
      SDL_GetGlobalMouseState(&mx,&my);

      if(SDL_BUTTON(SDL_GetGlobalMouseState(&mx,&my))<=0) {
        if(mx==0&&my==0) {
          if(getModule("apps")!=1) {
            t=std::system(("~/"+PEACH_FOLDER+"bin/apps &").c_str());
            setModule("apps",1);
          }
        } else if(mx==dm.w-1&&my==0) {
          if(getModule("software")!=1) {
            t=std::system(("~/"+PEACH_FOLDER+"bin/software-explorer &").c_str());
            setModule("software",1);
          }
        } else if(mx==0&&my==dm.h-1) {
          if(getModule("restart")!=1&&getModule("shutdown")!=1) {
            t=std::system(("~/"+PEACH_FOLDER+"bin/restart &").c_str());
            setModule("restart",1);
          }
        } else if(mx==dm.w-1&&my==dm.h-1) {
          if(getModule("shutdown")!=1&&getModule("restart")!=1) {
            t=std::system(("~/"+PEACH_FOLDER+"bin/shutdown &").c_str());
            setModule("shutdown",1);
          }
        } else if(mx>dm.w/2-368/2&&mx<(dm.w/2-368/2)+368&&my==dm.h-1) {
          if(getModule("panel")!=1) {
            t=std::system(("~/"+PEACH_FOLDER+"bin/panel &").c_str());
            setModule("panel",1);
          }
        }
      }

      if(getModule("action")==1) {
        t=std::system("poweroff &");
        setModule("action",0);
        t=std::system(("~/"+PEACH_FOLDER+"bin/desktop fade-out").c_str());
      } else if(getModule("action")==2) {
        t=std::system("reboot &");
        setModule("action",0);
        t=std::system(("~/"+PEACH_FOLDER+"bin/desktop fade-out").c_str());
      }

      SDL_Delay(35);
    }
    SDL_Quit();
    return 0;
}
