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
    const char *size_c = (size).c_str();
    terminal_set(size_c);
    terminal_set("window.title='JACKAL'");
    terminal_set("font: fonts/monaco.ttf, size=16x16");
    terminal_set("0x1000: fonts/dungeon.png, size=16x16");
}


Display::~Display(){}


void Display::refresh(){
    for (int row = 0; row<tiles.rows; ++row){
        for (int col=0; col<tiles.cols; ++col){
            string fore = tiles.getColorFore(row, col);
            string back = tiles.getColorBack(row, col);
            char tile = tiles.getRep(row, col);
            const char *output = ("[color="+fore+"][bkcolor="+back+"]"+tile).c_str();
            terminal_print(col+1, row+6, output);
        }
    }
    terminal_refresh();
}


void Display::update(const Subject &subject){
   return; 
}
