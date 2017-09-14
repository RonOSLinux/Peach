#! /bin/bash
cd ~/.peach/
g++ -std=c++14 -Os ./src/main.cpp -o ./bin/peach -lSDL2
g++ -std=c++14 -Os ./src/desktop.cpp -o ./bin/desktop -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/apps.cpp -o ./bin/apps -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/panel.cpp -o ./bin/panel -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/restart.cpp -o ./bin/restart -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/shutdown.cpp -o ./bin/shutdown -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/tutorial.cpp -o ./bin/tutorial -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/settings.cpp -o ./bin/settings -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/software-explorer.cpp -o ./bin/software-explorer -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/software-action.cpp -o ./bin/software-action
g++ -std=c++14 -Os ./src/upgrade.cpp -o ./bin/upgrade -lSDL2 -lSDL2_image -lSDL2_ttf
g++ -std=c++14 -Os ./src/upgrade-action.cpp -o ./bin/upgrade-action
g++ -std=c++14 -Os ./src/update-sources.cpp -o ./bin/update-sources
