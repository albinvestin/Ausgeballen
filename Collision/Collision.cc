#include "Collision.h"
#include <cmath>
#include <iostream>

using namespace std;

// checkTunneling kollar om två Movingobjects har överlappat varandra,
// genom att stega med en "stepsize" av hastigheten och kolla om de kolliderar.
// Om de kolliderar sätts positionerna och true returneras.
bool Collision::checkTunneling(shared_ptr<Movingobject> object1,
    shared_ptr<Movingobject> object2, int radius1, int radius2) noexcept
{
    double stepsize{0.01};

    double ob1movementx{stepsize * object1->getXSpeed()};
    double ob1movementy{stepsize * object1->getYSpeed()};
    double ob2movementx{stepsize * object2->getXSpeed()};
    double ob2movementy{stepsize * object2->getYSpeed()};

    int cob1x{object1->getXPosition()};
    int cob1y{object1->getYPosition()};
    int cob2x{object2->getXPosition()};
    int cob2y{object2->getYPosition()};

    double ob1x{(double)object1->getLastXPosition()};
    double ob1y{(double)object1->getLastYPosition()};
    double ob2x{(double)object2->getLastXPosition()};
    double ob2y{(double)object2->getLastYPosition()};

    double distance{sqrt(pow(ob1x - ob2x, 2) + pow(ob1y - ob2y, 2))};
    double cdistance{sqrt(pow(cob1x - cob2x, 2) + pow(cob1y - cob2y, 2))};

    if (distance < 25 * (radius1 + radius2))
    {
        if(cdistance > distance)
        {
            return false;
        }
        else
        {
            for (double i = 0; i < (1 / stepsize); i++)
            {
                if (distance <= (radius1 + radius2))
                {
                    object1->setXPosition(ceil(ob1x));
                    object1->setYPosition(ceil(ob1y));
                    object2->setXPosition(ceil(ob2x));
                    object2->setYPosition(ceil(ob2y));
                    return true;
                }
                else
                {
                    ob1x += ob1movementx;
                    ob1y += ob1movementy;
                    ob2x += ob2movementx;
                    ob2y += ob2movementy;
                    distance = sqrt(pow(ob1x - ob2x, 2) + pow(ob1y - ob2y, 2));
                }
            }
        }
    }
    return false;
}


//CheckTunneling mellan Movingobject och Obstacle...
bool Collision::checkTunneling(std::shared_ptr<Movingobject> object,
    std::shared_ptr<Obstacle> wall, int radius, bool standing) noexcept
{
    double stepsize{0.005};
    double objx{(double)object->getLastXPosition()};
    double objy{(double)object->getLastYPosition()};
    double cobjx{(double)object->getXPosition()};
    double cobjy{(double)object->getYPosition()};
    double objmovementx{stepsize * object->getXSpeed()};
    double objmovementy{stepsize * object->getYSpeed()};
    double wallx{(double)wall->getXStart()};
    double wally{(double)wall->getYStart()};

    double distance{objy - wally};
    double cdistance{cobjy - wally};
    if (standing)
    {
        distance = objx - wallx;
        cdistance = cobjx - wallx;
    }

    if (abs(distance) < 25 * radius)
    {
        if (abs(cdistance) > abs(distance) &&
            (((distance < 0) && (cdistance < 0)) ||
            ((distance > 0) && (cdistance > 0))))
        {
            return false;
        }
        else
        {
            for (double i{0}; i < (1/stepsize); i++)
            {
                if (abs(distance) <= radius)
                {
                    object->setXPosition(round(objx));
                    object->setYPosition(round(objy));
                    return true;
                }
                else
                {
                    objx += objmovementx;
                    objy += objmovementy;
                    if (standing)
                    {
                        distance = objx - wallx;
                    }
                    else
                    {
                        distance = objy - wally;
                    }
                }
            }
        }
    }
    return false;
}



//-----------------Player-Player------------------------

void Collision::checkCollision(shared_ptr<Player> player1,
    shared_ptr<Player> player2, Physics & physicsobject,
    Game const & gameobject) noexcept
{
    int playerradius{gameobject.getPlayerRadius()};
    if (checkTunneling(player1, player2, playerradius, playerradius))
    {
        physicsobject.collision(player1, player2, playerradius);
    }
}


//-----------------Player-Obstacle------------------------

void Collision::checkCollision(shared_ptr<Player> playerobject,
    shared_ptr<Obstacle> obstacleobject, Physics & physicsobject,
    Game const & gameobject) noexcept
{
    int playerradius{gameobject.getPlayerRadius()};
    bool standing{obstacleobject->getXStart() == obstacleobject->getXEnd()};

    if (standing)
    {
        if (checkTunneling(playerobject, obstacleobject, playerradius, standing))
        {
            physicsobject.collision(playerobject, standing);
        }
    }
    else //Horizontal obstacle
    {
        if (checkTunneling(playerobject, obstacleobject, playerradius, standing))
        {
            physicsobject.collision(playerobject, standing);
        }
    }
}


//-----------------Player-Projectile------------------------

bool Collision::checkCollision(shared_ptr<Player> playerobject,
    shared_ptr<Projectile> projectileobject, Physics & physicsobject,
    Points & pointsobject, Game const & gameobject) noexcept
{
    int playerradius{gameobject.getPlayerRadius()};
    int projectileradius{gameobject.getProjectileRadius()};

    if (checkTunneling(playerobject, projectileobject, playerradius, projectileradius))
    {
        physicsobject.collision(playerobject, projectileobject, pointsobject, playerradius, projectileradius);
        return true;
    }
    return false;
}


//-----------------Player-Powerup------------------------

void Collision::checkCollision(shared_ptr<Player> playerobject,
    shared_ptr<Powerup> powerupobject, Map & mapobject, Game const & gameobject) noexcept
{
    if(playerobject->isAlive())
    {
        int playerradius{gameobject.getPlayerRadius()};
        int powerupradius{gameobject.getPowerupRadius()};

        int xdiff{playerobject->getXPosition() - powerupobject->getXPosition()};
        int ydiff{playerobject->getYPosition() - powerupobject->getYPosition()};

        if (sqrt(pow(xdiff, 2) + pow(ydiff, 2)) <= (playerradius + powerupradius))
        //Collision if length between two center positions are smaller than their radius combined:
        {
            powerupobject->setXPosition(-10000);
            powerupobject->setYPosition(-10000);
            powerupobject->setActivePlayer(playerobject);
            powerupobject->toggleActivation();
            powerupobject->setTime();
            mapobject.togglePowerupPresent();
        }
    }
}


//-----------------Projectile-Projectile------------------------

//Sends bool to Map-class which if true, removes the two projectiles.
bool Collision::checkCollision(shared_ptr<Projectile> projectileone,
    shared_ptr<Projectile> projectiletwo, Game const & gameobject) noexcept
{
    int projectileradius{gameobject.getProjectileRadius()};
    return checkTunneling(projectileone, projectiletwo, projectileradius, projectileradius);
}


//-----------------Projectile-Obstacle------------------------

bool Collision::checkCollision(shared_ptr<Projectile> projectileobject,
    shared_ptr<Obstacle> obstacleobject, Game const & gameobject) noexcept
{
    int projectileradius{gameobject.getProjectileRadius()};
    bool standing{obstacleobject->getXStart() == obstacleobject->getXEnd()};

    if (standing)
    {
        bool left{obstacleobject->getXStart() == 0};
        if(left && projectileobject->getXPosition() <= projectileradius)
        {
            projectileobject->setXPosition(projectileradius);
            return true;
        }
        else if(!left && projectileobject->getXPosition() >= obstacleobject->getXStart() - projectileradius)
        {
            projectileobject->setXPosition(obstacleobject->getXStart() - projectileradius);
            return true;
        }
    }
    else //Horizontal obstacle
    {
        bool bottom{obstacleobject->getYStart() == 0};
        if(bottom && projectileobject->getYPosition() <= projectileradius)
        {
            projectileobject->setYPosition(projectileradius);
            return true;
        }
        else if(!bottom && projectileobject->getYPosition() >= obstacleobject->getYStart() - projectileradius)
        {
            projectileobject->setYPosition(obstacleobject->getYStart() - projectileradius);
            return true;
        }
    }
    return false;
}
