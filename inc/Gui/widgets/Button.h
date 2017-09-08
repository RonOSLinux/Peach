#ifndef _Widget_Button
#define _Widget_Button

class Button: public Widget {
private:
  SDL_Texture* text_tex;
  int text_w;
  int text_h;
  bool text=false;
  Image* img_img;
  bool image=false;
public:
  Button(const char* text,TTF_Font* font,int x,int y,int w,int h) {
    create(x,y,w,h);
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,{195,195,195}));
    TTF_SizeText(font,text,&text_w,&text_h);
    this->text=true;
  }
  Button(Image* img,int x,int y,int w,int h) {
    create(x,y,w,h);
    img_img=img;
    image=true;
  }
  Button(int x,int y,int w,int h) {
    create(x,y,w,h);
  }
  ~Button() {
    if(text) {
      SDL_DestroyTexture(text_tex);
    }
  }
  void display() {
    checkEvent();
    if(getEvent()==2) {
      renderFillRect(getX(),getY(),getWidth(),getHeight(),hover_color);
    } else if(getEvent()==1) {
      renderFillRect(getX(),getY(),getWidth(),getHeight(),hover_color);
    } else {
      renderFillRect(getX(),getY(),getWidth(),getHeight(),normal_color);
    }
    if(text) {
      renderCopyEx(text_tex,getX()+getWidth()/2-text_w/2,getY()+getHeight()/2-text_h/2,text_w,text_h);
    } else if(image) {
      img_img->setX(getX()+getWidth()/2-img_img->getWidth()/2);
      img_img->setY(getY()+getHeight()/2-img_img->getHeight()/2);
      img_img->display();
    }
  }
  void setText(const char* text,TTF_Font* font) {
    if(!this->text) {
      this->text=true;
      image=false;
    }
    text_tex=SDL_CreateTextureFromSurface(ren,TTF_RenderText_Blended(font,text,{225,225,255}));
    TTF_SizeText(font,text,&text_w,&text_h);
  }
  Image* getIMG() {
    return img_img;
  }
};

#endif
