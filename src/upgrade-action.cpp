#include <cstdlib>
#include <string>
#include "../inc/const.h"
#include "../inc/modules.h"

int main(int argc,char const *argv[]) {
  int t;
  if(argc>1) {
    std::string mode;
    mode=argv[1];
    if(mode=="update") {
      t=std::system("apt-get --assume-yes dist-upgrade");
    } else if(mode=="upgrade") {
      //scheiße ändern
      t=std::system("");
      /* test yes
      t=std::system("apt-get --assume-yes update");
      t=std::system("apt-get --assume-yes dist-upgrade");
      */
    }
    setModule("upgrade-action",1);
  }
  return 0;
}
