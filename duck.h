#ifndef DUCK_H
#define DUCK_H

#include <vector>

class Duck
{
public:
    Duck(int start, int l);

    void popDuck(int pos);
    bool contains(int i);
    bool isDestroyed();

private:
    int length_;
    std::vector<int> coords_;
    bool destroyed_;
};

#endif // DUCK_H
