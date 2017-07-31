#ifndef JACKAL_TILEGRID_H
#define JACKAL_TILEGRID_H
#include <memory>
#include <vector>
#include <string>

enum Color{
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
};

class TileGrid{
    
    /* A Tile is a data structure that represents a single tile in the grid.
     *  It has a name, and a representation, as well as a color and a walkable
     *  state. A Tile can also hold an actor and items (in the future).
     */
    struct Tile{
        const std::string name;
        const char rep;
        const bool walkable;
        const Color color;

        Tile(std::string name, char rep, bool walkable=true, Color color=WHITE)
            : name{name}, rep{rep}, walkable{walkable}, color{color} 
        {}
    };

    std::vector<std::unique_ptr<Tile>> tiles;
    const int rows;
    const int cols;

public:

    TileGrid(const std::string input, const int rows, const int cols);

    // Accessors for tiles in the grid
    std::string getName(const int row, const int col) const;
    
    char getRep(const int row, const int col) const;

    Color getColor(const int row, const int col) const;

    bool isWalkable(const int row, const int col) const;

};

#endif
