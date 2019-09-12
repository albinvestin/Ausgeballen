#ifndef POINTS_H
#define POINTS_H

#include <vector>
#include <stdexcept>

class Points_Error : public std::logic_error
{
    using std::logic_error::logic_error;
};

class Points
{
private:
    std::vector<int> playerpoints{};

public:
    Points(int);
    ~Points() = default;

    void increasePoints(int);
    int getPoints(int);
};

#endif
