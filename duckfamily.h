#ifndef DUCKFAMILY_H
#define DUCKFAMILY_H

#include <vector>

class DuckFamily
{
public:
    DuckFamily(int start, int l);

    int getLength();
    int getStart();
    void popDuck(int pos);
    bool contains(int i);
    bool isDestroyed();

private:
    int start_;
    int length_;
    std::vector<int> coords_;
    bool destroyed_;
};

#endif // DUCKFAMILY_H
