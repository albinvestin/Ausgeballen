#include "Player.h"
#include "../Map/Map.h"
#include "../Physics/Physics.h"

using namespace std;

//Constructor
Player::Player(int xpos, int ypos, double xspd, double yspd, double startangle, int index)
    : Movingobject{xpos, ypos, xpos, ypos, xspd, yspd}, gundirection{startangle}, playerindex{index}
    {}

//Functions
void Player::shoot(Map & world, Game const & gameobject) noexcept
{
    if (alive)
    {
        bool reloading{getReloadTime() != 0};
        if (!reloading)
        {
            world.addProjectile(*this, gameobject);
            double direction{getGunDirection() + M_PI};
            double newxspeed{(recoilspeed * cos(direction)) + getXSpeed()};
            double newyspeed{(recoilspeed * sin(direction)) + getYSpeed()};
            double newspeed = sqrt(pow(newxspeed, 2) + pow(newyspeed, 2));
            setReloadTime(30);
            if (newspeed > maxspeed)
            {
                setXSpeed(maxspeed * newxspeed / newspeed);
                setYSpeed(maxspeed * newyspeed / newspeed);
            }
            else
            {
                setXSpeed(newxspeed);
                setYSpeed(newyspeed);
            }
        }
    }
}

bool Player::isAlive() const noexcept
{
    return alive;
}

void Player::kill() noexcept
{
    alive = false;
    deathtime = 100;
}

void Player::revive() noexcept
{
    alive = true;
}

void Player::rotateGun() noexcept
{
    gundirection += (inversion * slowrotation * gunanglespeed);
    if (gundirection > 2*M_PI)
    {
        gundirection -= 2*M_PI;
    }
    else if(gundirection < 0)
    {
        gundirection += 2*M_PI;
    }
}

double Player::getGunDirection() const noexcept
{
    return gundirection;
}

int Player::getReloadTime() const noexcept
{
    return reloadtime;
}

void Player::updatePosition(Physics & physicsobject) noexcept
{
    int newxcoordinate{(int)round(xposition + xspeed)};
    int newycoordinate{(int)round(yposition + yspeed)};
    setLastXPosition(xposition);
    setLastYPosition(yposition);
    setXPosition(newxcoordinate);
    setYPosition(newycoordinate);
    physicsobject.friction(*this);
    rotateGun();
    if (deathtime == 1)
    {
        revive();
    }
    if (deathtime != 0)
    {
        deathtime--;
    }
    if (reloadtime != 0)
    {
        reloadtime--;
    }
}

int Player::getPlayerIndex() const noexcept
{
    return playerindex;
}

void Player::setReloadTime(int newtime) noexcept
{
    reloadtime = newtime;
}

double Player::getQuickProjectile() const noexcept
{
    return quickprojectile;
}

void Player::switchInversion() noexcept
{
    inversion = -inversion;
}

void Player::switchQuickProjectile() noexcept
{
    if (quickprojectile == 1)
    {
        quickprojectile = 3;
    }
    else
    {
        quickprojectile = 1;
    }
}

void Player::switchInvincibility() noexcept
{
    invincibility = !invincibility;
}

void Player::switchSlowRotation() noexcept
{
    if (slowrotation == 1)
    {
        slowrotation = 0.653;
    }
    else
    {
        slowrotation = 1;
    }
}

bool Player::getInvincibility() const noexcept
{
    return invincibility;
}
