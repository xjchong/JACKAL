#include "tilegrid.h"
using namespace std;


TileGrid::TileGrid(const string input, const int rows, const int cols)
    : rows{rows}, cols{cols}
{
    tiles.resize(rows*cols);
    setBoard(input);
}


void TileGrid::setBoard(string input){
    for (int i=0; i<tiles.size(); ++i){
        switch(input[i]){
            case '.':
                tiles[i]=make_unique<Tile>("floor", '.', true);
                break;
            case '+':
                tiles[i]=make_unique<Tile>("closed door", '+', false);
                break;
            case '\'':
                tiles[i]=make_unique<Tile>("open door", '\'', true);
                break;
            case '#':
                tiles[i]=make_unique<Tile>("wall", '#', false);
                break;
            default:
                tiles[i]=make_unique<Tile>("blank", '#', false);
        }
    }
    notify("new board");
}


string TileGrid::getName(const int row, const int col) const{
    if (row<0 || col<0 || row>rows || col>cols) return "invalid";
    else return tiles[row*cols + col]->name;
}


char TileGrid::getRep(const int row, const int col) const{
    if (row<0 || col<0 || row>rows || col>cols) return 0;
    else return tiles[row*cols + col]->rep;
}


bool TileGrid::isWalkable(const int row, const int col) const{
    if (row<0 || col<0 || row>rows || col>cols) return false;
    else return tiles[row*cols + col]->walkable;
}

