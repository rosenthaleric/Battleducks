#include "tile.h"
#include "duck.h"

#include <vector>
#include <set>

class Board
{
public:
    Board();
    bool check(int, int);
    void setDuck(int, int);
    void shoot(int);
    bool shootable(int);
private:
    std::vector<Tile*> tiles_;
    std::set<Duck*> ducks_;
};
