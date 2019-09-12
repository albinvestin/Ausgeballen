#include "Map.h"
#include "../Collision/Collision.h"
#include "../Movingobject/Movingobject.h"
#include "../Movingobject/Player.h"
#include "../Physics/Physics.h"

#include <iostream>
#include <cmath>

using namespace std;

// Uppdaterar all positioner, physics används till friktion för spelare
// och game till antal spelare.
void Map::updateAllPositions(Physics & physicsobject, Game const & gameobject) noexcept
{
    int numberofplayers{gameobject.getNumberOfPlayers()};
    for(int i{0}; i < numberofplayers; i++)
    {
        shared_ptr<Player> playerobject = getPlayer(i);
        playerobject->updatePosition(physicsobject);
    }

    int numberofprojectiles{(int)projectilelist.size()};
    for(int j{0}; j <= numberofprojectiles - 1; j++)
    {
        shared_ptr<Projectile> projectileobject = getProjectile(j);
        projectileobject->updatePosition();
    }
}


void Map::checkAllCollisions(Collision & collisionobject,
    Physics & physicsobject, Points & pointsobject, Game const & gameobject) noexcept
{
// Player Player kollisionstest
    int numberofplayers{gameobject.getNumberOfPlayers()};
    for (int i = 0; i < numberofplayers; i++)
    {
        shared_ptr<Player> player1 = getPlayer(i);
        for (int j = i + 1; j < numberofplayers; j++)
        {
            shared_ptr<Player> player2 = getPlayer(j);
            collisionobject.checkCollision(player1, player2, physicsobject, gameobject);
        }
    }


// Player Obstacle kollisionstest
    for (int i = 0; i < numberofplayers; i++)
    {
        shared_ptr<Player> playerobject = getPlayer(i);
        for (int j = 0; j < 4; j++)
        {
            shared_ptr<Obstacle> obstacleobject = getObstacle(j);
            collisionobject.checkCollision(playerobject, obstacleobject,
                physicsobject, gameobject);
        }
    }

// Player Projectile kollisionstest
    for (auto iterator1 = playerlist.begin(); iterator1 != playerlist.end(); ++iterator1)
    {
        shared_ptr<Player> playerobject = *iterator1;
        for (auto iterator2 = projectilelist.begin(); iterator2 != projectilelist.end();)
        {
            shared_ptr<Projectile> projectileobject = *iterator2;
            // Om checkCollision returnerar true har projektilen träffat
            // och skall tas bort.
            if (collisionobject.checkCollision(playerobject, projectileobject,
                physicsobject, pointsobject, gameobject))
            {
                iterator2 = projectilelist.erase(iterator2);
            }
            else
            {
                ++iterator2;
            }
        }
    }

// Projectile Projectile kollisionstest
    for (auto iterator1 = projectilelist.begin(); iterator1 != projectilelist.end();)
    {
        shared_ptr<Projectile> projectile1 = *iterator1;
        for (auto iterator2 = iterator1 + 1; iterator2 != projectilelist.end();)
        {
            shared_ptr<Projectile> projectile2 = *iterator2;
            // Om checkCollision returnerar true har projektilerna träffat
            // varandra och ska tas bort.
            if (collisionobject.checkCollision(projectile1, projectile2, gameobject))
            {
                iterator1 = projectilelist.erase(iterator1);
                iterator2 = projectilelist.erase(iterator2);
                iterator1--;
                break;
            }
            else
            {
                iterator2++;
            }
        }
        iterator1++;
    }

    //Projectile Obstacle Collision
    for (auto iterator1 = obstaclelist.begin(); iterator1 != obstaclelist.end();)
    {
        shared_ptr<Obstacle> obstacleobject = *iterator1;
        for (auto iterator2 = projectilelist.begin(); iterator2 != projectilelist.end();)
        {
            // Om checkCollision returnerar true har projektilen träffat
            // och ska tas bort.
            shared_ptr<Projectile> projectileobject = *iterator2;
            if (collisionobject.checkCollision(projectileobject, obstacleobject, gameobject))
            {
                iterator2 = projectilelist.erase(iterator2);
                break;
            }
            else
            {
                iterator2++;
            }
        }
        iterator1++;
    }

    //Player Powerup kollisionstest
    for (int i = 0; i < numberofplayers; i++)
    {
        shared_ptr<Player> playerobject = getPlayer(i);
        for (int j = 0; j < 4; j++)
        {
            shared_ptr<Powerup> powerupobject = getPowerup(j);
            collisionobject.checkCollision(playerobject, powerupobject, *this,
                 gameobject);
        }
    }



}

void Map::addPlayer(shared_ptr<Player> player) noexcept
{
    playerlist.push_back(player);
}

void Map::addObstacle(shared_ptr<Obstacle> obstacle) noexcept
{
    obstaclelist.push_back(obstacle);
}

void Map::addProjectile(Player const & shooter, Game const & gameobject) noexcept
{
    double direction{shooter.getGunDirection()};
    int projxpos{(int)(shooter.getXPosition() + round((gameobject.getPlayerRadius() + gameobject.getProjectileRadius()) * cos(direction)))};
    int projypos{(int)(shooter.getYPosition() + round((gameobject.getPlayerRadius() + gameobject.getProjectileRadius()) * sin(direction)))};
    double projxspeed{(double)(shooter.getXSpeed() + projectilespeed*cos(direction) * shooter.getQuickProjectile())};
    double projyspeed{(double)(shooter.getYSpeed() + projectilespeed*sin(direction) * shooter.getQuickProjectile())};
    int ownerindex{shooter.getPlayerIndex()};
    int shooterpos{shooter.getYPosition()};
    bool collision{false};

    //Går igenom objektlistan och kollar så att projektilen inte
    //genereras på andra sidan väggen från spelaren sett.
    for (auto iterator = obstaclelist.begin(); iterator != obstaclelist.end();)
    {
        shared_ptr<Obstacle> obstacleobject = *iterator;
        bool standing{obstacleobject->getXStart() == obstacleobject->getXEnd()};
        int obstaclepos{obstacleobject->getYStart()};
        if (standing)
        {
            obstaclepos = obstacleobject->getXStart();
            shooterpos = shooter.getXPosition();
            if ((projxpos > obstaclepos && shooterpos < obstaclepos) ||
                (projxpos < obstaclepos && shooterpos > obstaclepos))
            {
                collision = true;
                break;
            }
        }
        else
        {
            obstaclepos = obstacleobject->getYStart();
            shooterpos = shooter.getYPosition();
            if ((projypos > obstaclepos && shooterpos < obstaclepos) ||
                (projypos < obstaclepos && shooterpos > obstaclepos))
            {
                collision = true;
                break;
            }
        }
        iterator++;
    }

    //Om en kollision inte skett (d.v.s. spelaren skjuter inte rätt in i
    //en vägg) skapas en projektil.
    if (!collision)
    {
        shared_ptr<Projectile> currentprojectile{new Projectile(projxpos, projypos,
                                                projxspeed, projyspeed, ownerindex)};
        projectilelist.push_back(currentprojectile);
    }
}

shared_ptr<Player> Map::getPlayer(int index) const noexcept
{
    return playerlist.at(index);
}

shared_ptr<Obstacle> Map::getObstacle(int index) const noexcept
{
    return obstaclelist.at(index);
}

shared_ptr<Projectile> Map::getProjectile(int index) const noexcept
{
    return projectilelist.at(index);
}

shared_ptr<Powerup> Map::getPowerup(int index) const noexcept
{
    return poweruplist.at(index);
}

int Map::getProjectileSpeed() const noexcept
{
    return projectilespeed;
}

size_t Map::getProjectileListLength() const noexcept
{
    return projectilelist.size();
}

void Map::addPowerup(shared_ptr<Powerup> powerup) noexcept
{
    poweruplist.push_back(powerup);
}


bool Map::getPowerupPresent() const noexcept
{
    return poweruppresent;
}

void Map::togglePowerupPresent() noexcept
{
    poweruppresent = !poweruppresent;
}
