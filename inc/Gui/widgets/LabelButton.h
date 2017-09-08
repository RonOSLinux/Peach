#ifndef _Widget_LabelButton
#define _Widget_LabelButton

class LabelButton: public Widget {
private:
  SDL_Texture* text_tex;
  SDL_Texture* text_h_tex;
public:
  LabelButton(const char* text,TTF_Font* font,SDL_Color c,int x,int y) {
    int t_w,t_h;
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,c));
    text_h_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,{185,185,185}));
    TTF_SizeText(font,text,&t_w,&t_h);
    create(x,y,t_w,t_h);
  }
  ~LabelButton() {
    SDL_DestroyTexture(text_tex);
    SDL_DestroyTexture(text_h_tex);
  }
  void display() {
    checkEvent();
    if(getEvent()==0) {
      renderCopyEx(text_tex,getX(),getY(),getWidth(),getHeight());
    } else {
      renderCopyEx(text_h_tex,getX(),getY(),getWidth(),getHeight());
    }
  }
  void setText(const char* text,TTF_Font* font,SDL_Color c) {
    int t_w,t_h;
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,c));
    text_h_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,{195,195,195}));
    TTF_SizeText(font,text,&t_w,&t_h);
    setWidth(t_w);
    setHeight(t_h);
  }
};

#endif
