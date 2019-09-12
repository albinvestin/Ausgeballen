#include "Projectile.h"
#include <cmath>

using namespace std;

Projectile::Projectile(int xpos, int ypos, double xspd, double yspd,
    int ownerindex)
    : Movingobject{xpos, ypos, xpos, ypos, xspd, yspd}, owner{ownerindex}
    {}

int Projectile::getOwner() const noexcept
{
    return owner;
}

void Projectile::updatePosition() noexcept
{
    int newxcoordinate{(int)round(xposition + xspeed)};
    int newycoordinate{(int)round(yposition + yspeed)};
    setLastXPosition(xposition);
    setLastYPosition(yposition);
    setXPosition(newxcoordinate);
    setYPosition(newycoordinate);
}
