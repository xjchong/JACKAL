#ifndef JACKAL_DISPLAY_H
#define JACKAL_DISPLAY_H
#include "../board/observer.h"
#include <string>
#include <queue>
#include <vector>


// The unicodes for the background
const int base_ = 0x1060;
const int window_ = 0x201D;
const int window_n_ = window_ - 16;
const int window_s_ = window_ + 16;
const int window_w_ = window_ - 1;
const int window_e_ = window_ + 1;
const int window_nw_ = window_ - 17;
const int window_ne_ = window_ - 15;
const int window_sw_ = window_ + 15;
const int window_se_ = window_ + 17;

// The unicodes for the terrain tiles
const int floor_ = 0x1077;
const int wall_ = 0x1026;
const int wall_alt_ = 0x1020;
const int door_close_ = 0x10A0;
const int door_open_ = 0x10A1;
const int door_close_alt1_ = 0x10A2;
const int door_close_alt2_ = 0x10A3;
const int door_open_alt1_ = 0x10A5;
const int door_open_alt2_ = 0x10A4;
const int shadow_ = 0x10AF;

class TileGrid;
class Subject;

class Display : public Observer{

    const TileGrid &tiles;
    const int rows;
    const int cols;
    const int b_row;
    const int b_col;
    std::queue<std::string> messages;
    std::vector<int> doodad;

    void putTile(const int row, const int col, const int code);
    /* These are board displaying functions
     */
    void putBoard(const int row, const int col, const int code);
    void putFloor(const int row, const int col);
    void putWall(const int row, const int col);
    void putDoor(const int row, const int col);
    /* putTerrain(row, col) displays a single terrain tile.
     */
    void putTerrain(const int row, const int col);
    void refreshBoard();

    /* These are background displaying functions
     */
    void refreshBackground();
    void putWindow(const int y, const int x, const int dy, const int dx);

public:

    Display(TileGrid &tiles, const int rows=30, const int cols=48, const int b_row=4, const int b_col=1);
    ~Display();

    void refresh();

    void update(Subject &subject, std::string event) override;

};

#endif
