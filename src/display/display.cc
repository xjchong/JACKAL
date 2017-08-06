#include "display.h"
#include "../board/observer.h"
#include "../board/tilegrid.h"
#include <iostream>
#include <BearLibTerminal.h>
using namespace std;


static const int wall_layer = 0;
static const int floor_layer = 0; 
static const int door_layer = 2;
static const int door_layer2 = 3;
static const int shadow_layer = 1;


Display::Display(TileGrid &tiles, const int rows, const int cols, const int b_row, const int b_col)
    : tiles{tiles}, rows{rows}, cols{cols}, b_row{b_row}, b_col{b_col}
{
    string size = "window: size="+to_string(this->cols)+"x"+to_string(this->rows)+";";
    const char *size_c = (size).c_str();
    terminal_set(size_c);
    terminal_set("window.title='JACKAL'");
    terminal_set("font: fonts/monaco.ttf, size=32x32");
    terminal_set("0x1000: fonts/dungeon.png, size=16x16, resize=32x32, resize-filter=nearest");
}


Display::~Display(){}


void Display::refresh(){
    refreshBoard();
}


void Display::update(const Subject &subject){
   return; 
}


void Display::refreshBoard(){
    for (int i=0; i<=3; ++i){
        terminal_layer(i);
        terminal_clear_area(b_col, b_row, tiles.cols, tiles.rows);
    }
    for (int row=0; row<tiles.rows; ++row){
        for (int col=0; col<tiles.cols; ++col){
            putTerrain(row, col);
        }
    }
    terminal_refresh();
}


void Display::putTerrain(const int row, const int col){
    TerrainReference ref;
    if (tiles.getRep(row, col) == '.'){
        terminal_layer(floor_layer);
        terminal_put(col+b_col, row+b_row, ref.floor);
        if (row>0 && (tiles.getRep(row-1, col) == '#' || tiles.getRep(row-1, col) == '+')){
            terminal_layer(shadow_layer);
            terminal_put(col+b_col, row+b_row, ref.shadow);
        }
    }

    if (tiles.getRep(row, col) == '#'){
        terminal_layer(wall_layer);
        if (row == tiles.rows-1 || tiles.getRep(row+1, col) != '#'){
            terminal_put(col+b_col, row+b_row, ref.wall_alt);
        } else {
            terminal_put(col+b_col, row+b_row, ref.wall);
        }
    }

    if (tiles.getRep(row, col) == '+'){
        terminal_layer(floor_layer);
        terminal_put(col+b_col, row+b_row, ref.floor);
        if (tiles.getRep(row-1, col) != '.' || tiles.getRep(row+1, col) != '.'){
            if (tiles.getRep(row-1, col) == '#'){
                terminal_layer(shadow_layer);
                terminal_put(col+b_col, row+b_row, ref.shadow);
            }
            terminal_layer(door_layer);
            terminal_put(col+b_col, row+b_row, ref.door_close_alt1);
            terminal_layer(door_layer2);
            terminal_put(col+b_col, (row-1)+b_row, ref.door_close_alt2);
        } else {
        terminal_layer(door_layer);
            terminal_put(col+b_col, row+b_row, ref.door_close);
        }
    }

    if (tiles.getRep(row, col) == '\''){
        terminal_layer(floor_layer);
        terminal_put(col+b_col, row+b_row, ref.floor);
        terminal_layer(door_layer);
        if (tiles.getRep(row-1, col) != '.' || tiles.getRep(row+1, col) != '.'){
            terminal_put(col+b_col, row+b_row, ref.door_open_alt1);
            terminal_layer(door_layer2);
            terminal_put(col+b_col, (row-1)+b_row, ref.door_open_alt2);
        } else {
            terminal_put(col+b_col, row+b_row, ref.door_open);
        }
    }
}
