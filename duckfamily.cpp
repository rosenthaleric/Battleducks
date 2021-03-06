#include "duckfamily.h"
#include <vector>
#include <iostream>

/**
 *  Represents a duckfamily with a length of 2 to 5 tiles/ducks.
 *  Its occupied tiles are specified in its coordinates array.
 *  If one of its tiles is hit, the corresponding duck-coordinate
 *  gets popped out of the coords vector. If this vector is empty
 *  the duckFamily is destroyed.
 */

// start = first index of duck-coordinates of the family, left to right
DuckFamily::DuckFamily(int start, int l) : start_(start), length_(l),  coords_(length_), destroyed_(false) {
    for(int i = 0; i < length_; i++) {
        coords_[i] = start + i;
    }
}

int DuckFamily::getStart() {
    return start_;
}

int DuckFamily::getLength() {
    return length_;
}

// erase a hit duck coordinate from the family coords_ array
void DuckFamily::popDuck(int pos) {
    for(int i = 0; i < length_; i++) {
        if(pos == coords_[i]) {
            coords_.erase(coords_.begin() + i);
            break;
        }
    }
    if(coords_.empty()) destroyed_ = true;
}

// check if duck coords_ contain a certain coordinate
bool DuckFamily::contains(int i) {
    return std::find(coords_.begin(), coords_.end(), i) != coords_.end();
}

bool DuckFamily::isDestroyed() {
    return destroyed_;
}
