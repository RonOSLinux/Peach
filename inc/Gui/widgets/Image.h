#ifndef _Widget_Image
#define _Widget_Image

class Image: public Widget {
private:
  SDL_Texture* img_tex;
public:
  Image(SDL_Texture* img,int x,int y,int w,int h) {
    create(x,y,w,h);
    img_tex=img;
  }
  Image(SDL_Surface* img_sur,int x,int y,int w,int h) {
    create(x,y,w,h);
    img_tex=SDL_CreateTextureFromSurface(ren,img_sur);
  }
  void display() {
    renderCopyEx(img_tex,getX(),getY(),getWidth(),getHeight());
  }
  void setIMG(SDL_Texture* img) {
    img_tex=img;
  }
  void setIMG(SDL_Surface* img_sur) {
    img_tex=SDL_CreateTextureFromSurface(ren,img_sur);
  }
  SDL_Texture* getIMG() {
    return img_tex;
  }
};

#endif
