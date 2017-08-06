#ifndef JACKAL_DISPLAY_H
#define JACKAL_DISPLAY_H
#include "../board/observer.h"
#include <string>
#include <queue>
#include <vector>

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

    /* These are board displaying functions
     */
    void putFloor(const int row, const int col);
    void putWall(const int row, const int col);
    void putDoor(const int row, const int col);
    void refreshBoard();

    /* putTerrain(row, col) displays a single terrain tile.
     */
    void putTerrain(const int row, const int col);

public:

    Display(TileGrid &tiles, const int rows=21, const int cols=80, const int b_row=3, const int b_col=1);
    ~Display();

    void refresh();

    void update(Subject &subject, std::string event) override;

};

#endif
