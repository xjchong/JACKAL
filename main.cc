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
    int row = 39;
    int col = 47;
    WorldGen world{row, col};
    string board = world.generate(250);
    TileGrid tiles{board, row, col};
    Display display{tiles, 48, 64};
    display.refresh();
    while (x>=0 && y>=0){
        handleInput(x, y);
        display.refresh();
    }
    terminal_close();
}
