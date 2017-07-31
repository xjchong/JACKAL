#include "display.h"
#include "../board/observer.h"
#include "../board/tilegrid.h"
using namespace std;


Display::Display(WINDOW *window, TileGrid &tiles, const int rows, const int cols)
    : window{window}, tiles{tiles}, rows{rows}, cols{cols}
{}


Display::~Display(){}


void Display::refresh(){
    wclear(window);
    for (int row=0; row<rows; ++row){
        wmove(window, row+1, 0);
        for (int col=0; col<cols; ++col){
           waddch(window, tiles.getRep(row, col));
        }
    }
    wrefresh(window);    
}


void Display::update(const Subject &subject){
   return; 
}
