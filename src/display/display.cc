#include "display.h"
#include "../board/observer.h"
#include "../board/tilegrid.h"
#include <iostream>
#include <BearLibTerminal.h>
using namespace std;


Display::Display(TileGrid &tiles, const int rows, const int cols)
    : tiles{tiles}, rows{rows}, cols{cols}
{
    string size = "window: size="+to_string(this->cols)+"x"+to_string(this->rows)+";";
    string title = "window.title='JACKAL';";
    string font = "font: config/monaco.ttf, size=12;";
    const char *options = (size+title+font).c_str();
    terminal_set(options);
}


Display::~Display(){}


void Display::refresh(){
    for (int row = 0; row<tiles.rows; ++row){
        for (int col=0; col<tiles.cols; ++col){
            string fore = tiles.getColorFore(row, col);
            string back = tiles.getColorBack(row, col);
            char tile = tiles.getRep(row, col);
            const char *output = ("[color="+fore+"][bkcolor="+back+"]"+tile).c_str();
            terminal_print(col, row+1, output);
        }
    }
    terminal_refresh();
}


void Display::update(const Subject &subject){
   return; 
}
