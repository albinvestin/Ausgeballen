#include "Movingobject.h"

using namespace std;

//Constructor
Movingobject::Movingobject(int xpos, int ypos, int lastxpos, int lastypos, double xspd, double yspd)
    : xposition{xpos}, yposition{ypos}, lastxposition{lastxpos}, lastyposition{lastypos}, xspeed{xspd}, yspeed{yspd}
    {}

int Movingobject::getXPosition() const noexcept
{
    return xposition;
}

int Movingobject::getYPosition() const noexcept
{
    return yposition;
}

int Movingobject::getLastXPosition() const noexcept
{
    return lastxposition;
}

int Movingobject::getLastYPosition() const noexcept
{
    return lastyposition;
}

double Movingobject::getXSpeed() const noexcept
{
    return xspeed;
}

double Movingobject::getYSpeed() const noexcept
{
    return yspeed;
}

void Movingobject::setXPosition(int newxposition) noexcept
{
    xposition = newxposition;
}

void Movingobject::setYPosition(int newyposition) noexcept
{
    yposition = newyposition;
}

void Movingobject::setLastXPosition(int xpos) noexcept
{
    lastxposition = xpos;
}

void Movingobject::setLastYPosition(int ypos) noexcept
{
    lastyposition = ypos;
}

void Movingobject::setXSpeed(double newxspeed) noexcept
{
    xspeed = newxspeed;
}

void Movingobject::setYSpeed(double newyspeed) noexcept
{
    yspeed = newyspeed;
}
