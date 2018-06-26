#ifndef DUCK_H
#define DUCK_H

#include <vector>

/**
 *  Represents a duck entity with a length of 2 to 5 tiles.
 *  Its occupied tiles are specified in its coordinates array.
 *  If one of its tiles is hit, the corresponding coordinate
 *  gets popped out of the coords array.
 */

class Duck
{

public:
    Duck(int start, int l);

    void popDuck(int pos);
    bool contains(int i);
    bool isDestroyed();

private:
    int length_;
    vector<int> coords_;
    bool isDestroyed_;
};

Duck::Duck(int start, int l) : length_(l) {
    coords_ = new std::vector<int>(length_);
    for(int i = 0; i < length; i++) {
        coords_[i] = start + i;
    }
}

// erase a hit duck coordinate from its array
void Duck::popDuck(int pos) {
    for(int i = 0; i < length; i++) {
        if(pos == coords_[i]) {
            coords_.erase(coords.begin() + i);
            break;
        }
    }
    if(coords_empty()) isDestroyed = true;
}

// check if duck coordinates contain a certain coordinate
bool Duck::contains(int i) {
    return std::find(coords_.begin(), coords_.end(), i) != coords_.end();
}

bool Duck::isDestroyed() {
    return isDestroyed_;
}

#endif // DUCK_H
