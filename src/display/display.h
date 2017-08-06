#ifndef JACKAL_DISPLAY_H
#define JACKAL_DISPLAY_H
#include "../board/observer.h"
#include <string>
#include <queue>
#include <vector>

class TileGrid;
class Subject;

class Display : public Observer{


    struct TerrainReference{
        int floor = 0x1050;
        int wall = 0x1006;
        int wall_alt = 0x1000;
        int door_close = 0x10A0;
        int door_open = 0x10A1;
        int door_close_alt1 = 0x10A2;
        int door_close_alt2 = 0x10A3;
        int door_open_alt1 = 0x10A5;
        int door_open_alt2 = 0x10A4;
        int shadow = 0x10AF;
    };

    const TileGrid &tiles;
    const int rows;
    const int cols;
    const int b_row;
    const int b_col;
    std::queue<std::string> messages;

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

    void update(const Subject &subject, std::string event) override;

};

#endif
