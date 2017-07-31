#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include "src/board/tilegrid.h"
#include "src/display/display.h"
using namespace std;


void handleInput(int &x, int &y){
   int ch = getch();
   if (ch == 'q') { x=-1; y=-1; }
}


int main(int argc, char *argv[]){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    WINDOW *main = newwin(24, 80, 0, 0);
    keypad(main, TRUE);
    int x = 0, y = 0;
    ifstream fstream("config/example.txt");
    string board((istreambuf_iterator<char>(fstream)), istreambuf_iterator<char>());
    board.erase(remove(board.begin(), board.end(), '\n'), board.end());
    TileGrid tiles{board, 24, 80};
    Display display{main, tiles, 24, 80};
    display.refresh();
    while (x>=0 && y>=0){
        handleInput(x, y);
        display.refresh();
    }
    endwin();
}
