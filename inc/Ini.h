#ifndef _Ini
#define _Ini

#include <vector>
#include <string>

namespace sources {
  std::vector<std::string> apps;
  std::vector<std::string> install;
  std::vector<std::string> description;
  std::vector<int> categorie;
  std::vector<std::string> icon;

  void add(std::string name,std::string inst,std::string desc,int cat,std::string ic) {
    apps.push_back(name);
    install.push_back(inst);
    description.push_back(desc);
    categorie.push_back(cat);
    icon.push_back(ic);
  }

  void init() {
    add("Audacity","audacity","JACK-Audio compatible Audio editing tool",0,"audacity");
    add("Ardour","ardour","All-in one professional Audio-DAW",0,"ardour");
    add("Brasero","brasero","Easy to use DVD/CD-burner",0,"disk-burner");
    add("LMMS","lmms","Pattern based alround Audio-DAW",0,"lmms");
    add("PulseAudio Volume Control","pavucontrol","Controlls the PulseAudio Output and Input",0,"multimedia-volume-control");
    add("VLC media player","vlc","Very stable open-source Multimedia-Player",0,"vlc");
    add("Xfburn","xfburn","The Xfce DVD/CD-burner",0,"disk-burner");

    add("Geany","geany","Simple and lightweight IDE",1,"geany");

    add("Firefox Web Browser","firefox","Fast & Easy to use Web-Browser!",5,"firefox");
  }
}

#endif
