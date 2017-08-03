#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <BearLibTerminal.h>
#include "src/board/tilegrid.h"
#include "src/display/display.h"
using namespace std;


void handleInput(int &x, int &y){
   int key = terminal_read();
   if (key == TK_Q) { x=-1; y=-1; }
}


int main(int argc, char *argv[]){
    terminal_open();
    int x = 0, y = 0;
    ifstream fstream("config/example.txt");
    string board((istreambuf_iterator<char>(fstream)), istreambuf_iterator<char>());
    board.erase(remove(board.begin(), board.end(), '\n'), board.end());
    TileGrid tiles{board, 21, 80};
    Display display{tiles, 24, 80};
    display.refresh();
    while (x>=0 && y>=0){
        handleInput(x, y);
        display.refresh();
    }
    terminal_close();
}
