#include "Powerup.h"

using namespace std;

// Constructor
Powerup::Powerup(int x, int y, int dur)
    : xposition{x}, yposition{y}, duration{dur}
    {}

/* Get/set functions */
int Powerup::getXPosition() const noexcept
{
    return xposition;
}

int Powerup::getYPosition() const noexcept
{
    return yposition;
}

void Powerup::setXPosition(int value) noexcept
{
    xposition = value;
}

void Powerup::setYPosition(int value) noexcept
{
    yposition = value;
}

bool Powerup::decreaseTime() noexcept
{
    if(poweruptime > 0)
    {
        --poweruptime;
        return true;
    }
    else
    {
        return false;
    }
}

void Powerup::setTime() noexcept
{
    poweruptime = duration;
}

int Powerup::getTime() const noexcept
{
    return poweruptime;
}

shared_ptr<Player> Powerup::getActivePlayer() const noexcept
{
    return activeplayer;
}

void Powerup::setActivePlayer(shared_ptr<Player> playerobject) noexcept
{
    activeplayer = playerobject;
}



/* Subclass Inversion */

Inversion::Inversion(int xpos, int ypos, int dur)
    : Powerup{xpos, ypos, dur} {}

void Inversion::toggleActivation() noexcept
{
    activeplayer->switchInversion();
}


/* Subclass Invincibility */

Invincibility::Invincibility(int xpos, int ypos, int dur)
    : Powerup{xpos, ypos, dur} {}

void Invincibility::toggleActivation() noexcept
{
    activeplayer->switchInvincibility();
}


/* Subclass Quickprojectile */

Quickprojectile::Quickprojectile(int xpos, int ypos, int dur)
    : Powerup{xpos, ypos, dur} {}

void Quickprojectile::toggleActivation() noexcept
{
    activeplayer->switchQuickProjectile();
}


/* Subclass Slowrotation */

Slowrotation::Slowrotation(int xpos, int ypos, int dur)
    : Powerup{xpos, ypos, dur} {}

void Slowrotation::toggleActivation() noexcept
{
    activeplayer->switchSlowRotation();
}
