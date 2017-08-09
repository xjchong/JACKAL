#include "display.h"
#include "../board/observer.h"
#include "../board/tilegrid.h"
#include <iostream>
#include <BearLibTerminal.h>
#include <random>
#include <cmath>
using namespace std;


static const int bg_layer = 0;
static const int bg_layer2 = 1;
static const int text_layer = 2;
static const int wall_layer = 3;
static const int floor_layer = 3; 
static const int door_layer = 5;
static const int door_layer2 = 6;
static const int shadow_layer = 4;


Display::Display(TileGrid &tiles, const int rows, const int cols, const int b_row, const int b_col)
    : tiles{tiles}, rows{rows}, cols{cols}, b_row{b_row}, b_col{b_col}
{
    terminal_setf("window: size=%dx%d", cols*2, rows*2);
    terminal_set("window.title='JACKAL'");
    terminal_set("font: fonts/header.ttf, size=16x16");
    terminal_set("0x1000: fonts/dungeon.png, size=16x16, resize=32x32, resize-filter=nearest, align=top-left");
    terminal_set("0x2000: fonts/interface.png, size=16x16");
    doodad.resize(rows*cols);
    update(tiles, "new board");
    terminal_layer(text_layer);
    terminal_print(2, 2, "The skeleton archer fires a poisonous arrow at you!");
    terminal_print(2, 3, "You feel sick! You swing at the skeleton archer and miss.");
    terminal_print(2, 4, "The skeleton archer flees in terror!");
    terminal_print(2, 5, "You feel a little better. You realize that you are invisible.");
    refreshBackground();
}


Display::~Display(){}


void Display::refresh(){
    refreshBoard();
}


void Display::update(Subject &subject, string event){
   if (event == "new board"){
       random_device rnd;
       mt19937 mt{rnd()};
       normal_distribution<> wall{0, 2};
       normal_distribution<> floor{4, 2};
       for (int row=0; row<tiles.rows; ++row){
            for (int col=0; col<tiles.cols; ++col){
                int serial = 0;
                if (tiles.getRep(row, col) == '#'){
                    serial = wall(mt);
                    if (serial>5) serial = 5;
                } else if (tiles.getRep(row, col) == '.'){
                    serial = floor(mt);
                    if (serial>7) serial = 7;
                }
                doodad[row*tiles.cols +col] = serial<0? 0 : serial;
            }
       }
   }
}


void Display::refreshBoard(){
    for (int i=floor_layer; i<=door_layer2; ++i){
        terminal_layer(i);
        terminal_clear_area(b_col*2, b_row*2, tiles.cols*2, tiles.rows*2);
    }
    for (int row=0; row<tiles.rows; ++row){
        for (int col=0; col<tiles.cols; ++col){
            putTerrain(row, col);
        }
    }
    terminal_refresh();
}


void Display::putTile(const int row, const int col, const int code){
    terminal_put(col*2, row*2, code);
}


void Display::putBoard(const int row, const int col, const int code){
    putTile(row+b_row, col+b_col, code);
}


void Display::putTerrain(const int row, const int col){
    char rep = tiles.getRep(row, col);
    switch(rep){
        case '.': return putFloor(row, col);
        case '#': return putWall(row, col);
        case '+': return putDoor(row, col);
        case '\'': return putDoor(row, col);
        default: return;
    }
}


void Display::putFloor(const int row, const int col){
    if (tiles.getRep(row, col) == '.'){
        terminal_layer(floor_layer);
        putBoard(row, col, floor_+doodad[row*tiles.cols +col]);
        if (row>0 && (tiles.getRep(row-1, col) == '#' || tiles.getRep(row-1, col) == '+')){
            terminal_layer(shadow_layer);
            putBoard(row, col, shadow_);
        }
    }
}


void Display::putWall(const int row, const int col){
    if (tiles.getRep(row, col) == '#'){
        terminal_layer(wall_layer);
        if (row == tiles.rows-1 || tiles.getRep(row+1, col) != '#'){
            putBoard(row, col, wall_alt_+doodad[row*tiles.cols +col]);
        } else if ((col == 0 && tiles.getRep(row, col+1) == '.')
            || (col == tiles.cols-1  && tiles.getRep(row, col-1) == '.')
            || (tiles.getRep(row, col-1) == '.' && tiles.getRep(row, col+1) == '.')){
            putBoard(row, col, wall_+doodad[row*tiles.cols +col]);
        } else {
            putBoard(row, col, wall_);
        }
    }
}


void Display::putDoor(const int row, const int col){
    int door = tiles.getRep(row, col) == '+'? door_close_ : door_open_;
    int door_alt1 = tiles.getRep(row, col) == '+'? door_close_alt1_ : door_open_alt1_;
    int door_alt2 = tiles.getRep(row, col) == '+'? door_close_alt2_ : door_open_alt2_;

    terminal_layer(floor_layer);
    putBoard(row, col, floor_);
    terminal_layer(door_layer);
    if (tiles.getRep(row, col-1) != '.' || tiles.getRep(row, col+1) != '.'){ 
        putBoard(row, col, door);
    } else {
        putBoard(row, col, door_alt1);
        terminal_layer(door_layer2);
        putBoard(row-1, col, door_alt2);
    }

    if (tiles.getRep(row-1, col) == '#'){
        terminal_layer(shadow_layer);
        putBoard(row, col, shadow_);
    }

}


void Display::refreshBackground(){
    terminal_layer(bg_layer);
    for (int row=0; row<rows*2; ++row){
        for (int col=0; col<cols*2; ++col){   
            terminal_put(col, row, base_);
        }
    }
    putWindow(0, 0, rows*2, (tiles.cols+2)*2);
    putWindow(0, (tiles.cols+2)*2, (rows*2)/3, (cols-(tiles.cols+2))*2);
    putWindow((rows*2)/3, (tiles.cols+2)*2, (rows*4)/3, (cols-(tiles.cols+2))*2);
    terminal_refresh();
}


void Display::putWindow(const int y, const int x, const int dy, const int dx){
    terminal_layer(bg_layer2);
    for (int row=0; row<dy; ++row){
        for (int col=0; col<dx; ++col){
            if (row==0) terminal_put(col+x, row+y, window_n_);
            else if (row==dy-1) terminal_put(col+x, row+y, window_s_);
            else if (col==0) terminal_put(col+x, row+y, window_w_);
            else if (col==dx-1) terminal_put(col+x, row+y, window_e_);
            else terminal_put(col+x, row+y, window_);
        }
    }
    terminal_put(x, y, window_nw_);
    terminal_put(x+dx-1, y, window_ne_);
    terminal_put(x, y+dy-1, window_sw_);
    terminal_put(x+dx-1, y+dy-1, window_se_);
}
