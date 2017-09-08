#ifndef _gui
#define _gui

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace Gui {
  /* ! Global ! */
  SDL_Window* wnd; //Gui::wnd
  SDL_Renderer* ren; //Gui::ren
  int gmousex;
  int gmousey;
  int mousex;
  int mousey;
  Uint32 mousetimer;
  TTF_Font* f_reg_big;
  TTF_Font* f_reg_med;
  TTF_Font* f_reg_sma;
  TTF_Font* f_light_big;
  TTF_Font* f_light_med;
  TTF_Font* f_light_sma;
  SDL_Color normal_color={25,25,25,185};
  SDL_Color hover_color={0,185,235,185};
  bool prefer_global_mouse=false;
  SDL_DisplayMode dm;
  int wnd_x;
  int wnd_y;

  /* Functions */
  inline void init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
  }

  inline void quit() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
  }

  inline void loadFonts(const char* path_reg,const char* path_light) {
    f_reg_big=TTF_OpenFont(path_reg,45);
    f_reg_med=TTF_OpenFont(path_reg,28);
    f_reg_sma=TTF_OpenFont(path_reg,18);
    f_light_big=TTF_OpenFont(path_light,45);
    f_light_med=TTF_OpenFont(path_light,28);
    f_light_sma=TTF_OpenFont(path_light,18);
  }

  inline void renderDrawRect(int x,int y,int w,int h,SDL_Color c) {
    SDL_Rect trect={x,y,w,h};
    SDL_SetRenderDrawColor(ren,c.r,c.g,c.b,c.a);
    SDL_RenderDrawRect(ren,&trect);
  }

  inline void renderFillRect(int x,int y,int w,int h,SDL_Color c) {
    SDL_Rect trect={x,y,w,h};
    SDL_SetRenderDrawColor(ren,c.r,c.g,c.b,c.a);
    SDL_RenderFillRect(ren,&trect);
  }

  inline void renderCopyEx(SDL_Texture* tex,int x,int y,int w,int h) {
    SDL_Rect trect={x,y,w,h};
    SDL_RenderCopy(ren,tex,NULL,&trect);
  }

  /* Includes */
  #include "Widget.h"
  #include "widgets/Image.h"
  #include "widgets/Button.h"
  #include "widgets/Label.h"
  #include "widgets/ExitBtn.h"
  #include "widgets/CheckButton.h"
  #include "widgets/ProgressBar.h"
  #include "widgets/LabelButton.h"
  #include "widgets/ProgressWait.h"
  #include "Tooltip.h"
  #include "Window.h"
}

#endif
