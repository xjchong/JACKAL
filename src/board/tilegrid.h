#ifndef JACKAL_TILEGRID_H
#define JACKAL_TILEGRID_H
#include <memory>
#include <vector>
#include <string>

enum Color{
    BLACK=0,
    RED=1,
    GREEN=2,
    YELLOW=3,
    BLUE=4,
    MAGENTA=5, 
    CYAN=6,
    WHITE=7
};

class TileGrid{
    
    /* A Tile is a data structure that represents a single tile in the grid.
     *  It has a name, and a representation, as well as a color and a walkable
     *  state. A Tile can also hold an actor and items (in the future).
     */
    struct Tile{
        std::string name;
        char rep;
        bool walkable;
        std::string color_fore;
        std::string color_back;

        Tile(std::string name
                , char rep
                , bool walkable=true
                , std::string color_fore="white"
                , std::string color_back="black")
            : name{name}
            , rep{rep}
            , walkable{walkable}
            , color_fore{color_fore}
            , color_back{color_back}
        {}
    };

    std::vector<std::unique_ptr<Tile>> tiles;

public:

    const int rows;
    const int cols;

    TileGrid(const std::string input, const int rows, const int cols);

    // Accessors for tiles in the grid
    std::string getName(const int row, const int col) const;
    
    char getRep(const int row, const int col) const;

    std::string getColorFore(const int row, const int col) const;

    std::string getColorBack(const int row, const int col) const;

    bool isWalkable(const int row, const int col) const;


};

#endif
