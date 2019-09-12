#include "Obstacle.h"

Obstacle::Obstacle(int startx, int starty, int endx, int endy)
    : xstart{startx}, ystart{starty}, xend{endx}, yend{endy}
    {}

int Obstacle::getXStart() const noexcept
{
    return xstart;
}

int Obstacle::getXEnd() const noexcept
{
    return xend;
}

int Obstacle::getYStart() const noexcept
{
    return ystart;
}

int Obstacle::getYEnd() const noexcept
{
    return yend;
}
