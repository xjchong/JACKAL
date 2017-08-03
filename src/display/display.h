#ifndef JACKAL_DISPLAY_H
#define JACKAL_DISPLAY_H
#include "../board/observer.h"
#include <string>
#include <queue>
#include <vector>

class TileGrid;
class Subject;

class Display : public Observer{

    const TileGrid &tiles;
    const int rows;
    const int cols;
    std::queue<std::string> messages;

public:

    Display(TileGrid &tiles, const int rows=21, const int cols=80);
    ~Display();

    void refresh();

    void update(const Subject &subject) override;

};

#endif
