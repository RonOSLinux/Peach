#ifndef _Widget_Label
#define _Widget_Label

class Label: public Widget {
private:
  SDL_Texture* text_tex;
public:
  Label(const char* text,TTF_Font* font,SDL_Color c,int x,int y) {
    int t_w,t_h;
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,c));
    TTF_SizeText(font,text,&t_w,&t_h);
    create(x,y,t_w,t_h);
  }
  ~Label() {
    SDL_DestroyTexture(text_tex);
  }
  void display() {
    renderCopyEx(text_tex,getX(),getY(),getWidth(),getHeight());
  }
  void setText(const char* text,TTF_Font* font,SDL_Color c) {
    int t_w,t_h;
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,c));
    TTF_SizeText(font,text,&t_w,&t_h);
    setWidth(t_w);
    setHeight(t_h);
  }
};

#endif
