#include <cstdlib>
#include <string>
#include "../inc/const.h"
#include "../inc/modules.h"

int main(int argc,char const *argv[]) {
  int t;
  if(argc>2) {
    std::string mode;
    std::string app;
    mode=argv[1];
    app=argv[2];
    if(mode=="install") {
      t=std::system("gksudo \'apt-get --assume-yes update\'");
      t=std::system(("gksudo \'apt-get --assume-yes install "+app+"\'").c_str());
    } else if(mode=="remove") {
      t=std::system("gksudo \'apt-get --assume-yes update\'");
      t=std::system(("gksudo \'apt-get --assume-yes remove "+app+"\'").c_str());
    }
    setModule("software-action",1);
  }
  return 0;
}
