#ifndef _Widget_ExitBtn
#define _Widget_ExitBtn

class ExitBtn: public Widget {
private:
  Label* normal;
  Label* hover;
  TTF_Font* f;
public:
  ExitBtn(const char* f_path,int x,int y) {
    f=TTF_OpenFont(f_path,120);
    normal=new Label("x",f,{195,195,195},x,y);
    normal->setWidth(35);
    normal->setHeight(64);
    hover=new Label("x",f,{245,245,245},x,y);
    hover->setWidth(35);
    hover->setHeight(64);
    create(x,y,35,64);
  }
  ~ExitBtn() {
    delete normal;
    delete hover;
    normal->~Label();
    hover->~Label();
  }
  void display() {
    checkEvent();
    if(getEvent()==1||getEvent()==2) {
      hover->display();
    } else {
      normal->display();
    }
  }
};

#endif
