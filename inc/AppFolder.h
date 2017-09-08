#ifndef _AppFolder
#define _AppFolder

#include <array>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <sstream>

class AppFolder {
private:
  std::array<std::string, 10> cat_shown_names={ {"Multimedia",
                                                 "Development",
                                                 "Education",
                                                 "Games",
                                                 "Graphics",
                                                 "Internet",
                                                 "Office",
                                                 "Science",
                                                 "System",
                                                 "Accessories"} };

  std::array<std::string, 10> cat_real_names={ {"AudioVideo",
                                                "Development",
                                                "Education",
                                                "Game",
                                                "Graphics",
                                                "Network",
                                                "Office",
                                                "Science",
                                                "System",
                                                "Utility"} };

  std::vector<std::string> available_apps;
  std::vector<std::string> available_apps_cats;

  std::string __deletemarks(std::string s) {
    std::array<std::string, 7> marks={{"%f","%F","%u",
                                      "%U","%i","%c",
                                      "%k"}};
    bool positive=false;
    int pos=0;
    for(int i=0;i<s.length()-1;i++) {
      for(int j=0;j<7;j++) {
        if(s.substr(i,2)==marks[j]) {
          positive=true;
          pos=i;
          break;
        }
      }
    }
    if(positive) {
      return s.substr(0,pos-1);
    }
    return s;
  }
  std::vector<std::string> __split(std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while(std::getline(ss, item, delim)) {
      tokens.push_back(item);
    }
    return tokens;
  }
  std::string __firstcat(std::string s) {
    std::vector<std::string> cats=__split(s,';');
    bool found=false;
    std::string cat="";
    std::sort(cats.begin(),cats.end());
    for(auto t: cats) {
      for(auto c: cat_real_names) {
        if(t==c) {
          found=true;
          cat=c;
          break;
        }
      }
      if(found) {
        break;
      }
    }
    return cat;
  }
public:
  AppFolder() {

  }
  ~AppFolder() {

  }
  std::string getRealName(std::string desk_file) {
    std::ifstream app_name;
    app_name.open("/usr/share/applications/"+desk_file,std::ios_base::in);
    if(app_name.is_open()) {
      std::string temp;
      while(!app_name.eof()) {
        std::getline(app_name,temp);
        if(temp.length()>6&&temp.substr(0,4)=="Name"&&temp.substr(4,1)=="=") {
          return temp.substr(5,temp.length()-5);
        }
      }
      app_name.close();
    }
    return "";
  }
  std::string getIconName(std::string desk_file) {
    std::ifstream icon_name;
    icon_name.open("/usr/share/applications/"+desk_file,std::ios_base::in);
    if(icon_name.is_open()) {
      std::string temp;
      while(!icon_name.eof()) {
        std::getline(icon_name,temp);
        if(temp.length()>6&&temp.substr(0,4)=="Icon"&&temp.substr(4,1)=="=") {
          return temp.substr(5,temp.length()-5)+".svg";
        }
      }
      icon_name.close();
    }
    return "";
  }
  std::string getExecPath(std::string desk_file) {
    std::ifstream icon_name;
    icon_name.open("/usr/share/applications/"+desk_file,std::ios_base::in);
    if(icon_name.is_open()) {
      std::string temp;
      while(!icon_name.eof()) {
        std::getline(icon_name,temp);
        if(temp.length()>6&&temp.substr(0,4)=="Exec"&&temp.substr(4,1)=="=") {
          return __deletemarks(temp.substr(5,temp.length()-5));
        }
      }
      icon_name.close();
    }
    return "";
  }
  std::string getCategorie(std::string desk_file) {
    std::ifstream cat_name;
    cat_name.open("/usr/share/applications/"+desk_file,std::ios_base::in);
    if(cat_name.is_open()) {
      std::string temp;
      while(!cat_name.eof()) {
        std::getline(cat_name,temp);
        if(temp.length()>13&&temp.substr(0,11)=="Categories=") {
          return __firstcat(temp.substr(11,temp.length()-11));
        }
      }
    }
    return "";
  }
  void init() {
    DIR* dirHandle;
    struct dirent* dirEntry;
    std::string temp="";

    dirHandle=opendir("/usr/share/applications/");
    if(dirHandle!=NULL) {
      while(0!=(dirEntry=readdir(dirHandle))) {
        temp=dirEntry->d_name;
        if(temp.length()>8) {
          if(temp.substr(temp.length()-8,8)==".desktop"&&temp.substr(0,4)!="exo-") {
            for(int c=0;c<10;c++) {
              if(cat_real_names[c]==getCategorie(temp)) {
                available_apps_cats.push_back(cat_shown_names[c]);
                available_apps.push_back(temp);
                break;
              }
            }
          }
        }
      }
      closedir(dirHandle);
    }
  }
  void clearAll() {
    available_apps.clear();
    available_apps_cats.clear();
  }

  std::array<std::string,10> getShownNames() {
    return cat_shown_names;
  }

  std::vector<std::string> getAvailableApps() {
    return available_apps;
  }

  std::vector<std::string> getAvailableCats() {
    return available_apps_cats;
  }
};

#endif
