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
    add("Rythmbox","rythmbox","GNOME's default music player",0,"multimedia-audio-player");
    add("Amarok","amarok","Feature-filled music management tool",0,"amarok");
    add("Banshee","banshee","Powerful quality music player",0,"banshee");
    add("Exaile","exaile","Feature-filled music management tool",0,"exaile");
    add("Audacious","audacious","Very lightweight music player",0,"audacious");
    add("Totem","totem","GNOME's default video player",0,"totem");
    add("MPlayer","mplayer","Undefeatable Multimedia-Player",0,"mplayer");
    add("Kaffeine","kaffeine","KDE's default All-in one Multimedia-Player",0,"kaffeine");
    add("Kdenlive","kdenlive","Not Linear Video Editing Tool",0,"kdenlive");

    add("Geany","geany","Simple and lightweight IDE",1,"geany");
    add("Anjuta","anjuta","IDE with a large language support",1,"anjuta");
    add("Bluefish","blufish","IDE that focuses on Web-Development",1,"bluefish");
    add("CodeLite","codelite","Focuses on C & C++ Development",1,"text-editor");
    add("Code::Blocks IDE","codeblocks","Full C and C++ support",1,"codeblocks");
    add("DrPython","drpython","IDE for Python",1,"python");
    add("Eclipse","eclipse","Allround IDE for nearly any case",1,"eclipse");
    add("Mousepad","mousepad","Simple and lightweight IDE",1,"text-editor");

    add("Firefox Web Browser","firefox","Fast & Easy to use Web-Browser!",5,"firefox");
  }
}

#endif
