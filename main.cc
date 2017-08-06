#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <BearLibTerminal.h>
#include "src/board/tilegrid.h"
#include "src/display/display.h"
#include "src/board/worldgen.h"
using namespace std;


void handleInput(int &x, int &y){
   int key = terminal_read();
   if (key == TK_Q) { x=-1; y=-1; }
}


int main(int argc, char *argv[]){
    terminal_open();
    int x = 0, y = 0;
    // row 39, col 47, 48x64
    int row = 25;
    int col = 31;
    WorldGen world{row, col};
    TileGrid tiles{world.generate(250), row, col};
    Display display{tiles, 30, 48};
    display.refresh();
    while (x>=0 && y>=0){
        handleInput(x, y);
        tiles.setBoard(world.generate(250));
        display.refresh();
    }
    terminal_close();
}
