#ifndef JACKAL_TILEGRID_H
#define JACKAL_TILEGRID_H
#include <memory>
#include <vector>
#include <string>


class TileGrid{
    
    /* A Tile is a data structure that represents a single tile in the grid.
     *  It has a name, and a representation, as well as a color and a walkable
     *  state. A Tile can also hold an actor and items (in the future).
     */
    struct Tile{
        std::string name;
        char rep;
        bool walkable;

        Tile(std::string name, char rep, bool walkable=true)
            : name{name}
            , rep{rep}
            , walkable{walkable}
        {}
    };

    std::vector<std::unique_ptr<Tile>> tiles;

public:

    const int rows;
    const int cols;

    TileGrid(const std::string input, const int rows, const int cols);

    // setBoard(board) resets the grid to have a new set of tiles
    void setBoard(std::string input);

    // Accessors for tiles in the grid
    std::string getName(const int row, const int col) const;
    
    char getRep(const int row, const int col) const;

    void setRep(const int row, const int col, char rep);

    bool isWalkable(const int row, const int col) const;


};

#endif
