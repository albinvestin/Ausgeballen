#include "Physics.h"
#include "../Movingobject/Player.h"
#include "../Movingobject/Projectile.h"
#include <cmath>

using namespace std;


void Physics::friction(Player & playerobject) noexcept
{
    double xspeed{playerobject.getXSpeed()};
    double yspeed{playerobject.getYSpeed()};
    double totspeed{sqrt(pow(xspeed,2) + pow(yspeed, 2))};

    if(totspeed < frictionvalue)
    {
        playerobject.setXSpeed(0);
        playerobject.setYSpeed(0);
    }
    else if(totspeed != 0)
    {
        double xfactor{xspeed/totspeed};
        double yfactor{yspeed/totspeed};
        playerobject.setXSpeed(xspeed - xfactor*frictionvalue);
        playerobject.setYSpeed(yspeed - yfactor*frictionvalue);
    }

}


//-----------------Player-Player------------------------

void Physics::collision(shared_ptr<Player> player1, shared_ptr<Player> player2,
    int) noexcept
{
    int p1xpos{player1->getXPosition()};
    int p1ypos{player1->getYPosition()};
    int p2xpos{player2->getXPosition()};
    int p2ypos{player2->getYPosition()};

    double p1xspeed{player1->getXSpeed()};
    double p1yspeed{player1->getYSpeed()};
    double p2xspeed{player2->getXSpeed()};
    double p2yspeed{player2->getYSpeed()};

    //Elastisk stöt
    double dotproduct = (((p1xspeed - p2xspeed) * (p1xpos - p2xpos))
    + ((p1yspeed - p2yspeed) * (p1ypos - p2ypos))) / (pow(p1xpos - p2xpos, 2) + pow(p1ypos - p2ypos, 2));
    player1->setXSpeed(p1xspeed - (dotproduct * (p1xpos - p2xpos)));
    player1->setYSpeed(p1yspeed - (dotproduct * (p1ypos - p2ypos)));
    player2->setXSpeed(p2xspeed - (dotproduct * (p2xpos - p1xpos)));
    player2->setYSpeed(p2yspeed - (dotproduct * (p2ypos - p1ypos)));
}


//-----------------Player-Obstacle------------------------

//Funktionen tar in en bool som är true om hindret är vertikalt/stående.
void Physics::collision(shared_ptr<Player> playerobject, bool standing) noexcept
{
    if(standing)
    {
        playerobject->setXSpeed(-1 * playerobject->getXSpeed());
    }
    else
    {
        playerobject->setYSpeed(-1 * playerobject->getYSpeed());
    }
}


//-----------------Player-Projectile------------------------

void Physics::collision(std::shared_ptr<Player> playerobject,
    std::shared_ptr<Projectile> projectileobject, Points & pointsobject,
    int playerradius, int projectileradius) noexcept
{
    int playerxpos{playerobject->getXPosition()};
    int playerypos{playerobject->getYPosition()};
    int projectilexpos{projectileobject->getXPosition()};
    int projectileypos{projectileobject->getYPosition()};

    double playerxspeed{playerobject->getXSpeed()};
    double playeryspeed{playerobject->getYSpeed()};
    double projectilexspeed{projectileobject->getXSpeed()};
    double projectileyspeed{projectileobject->getYSpeed()};

    //Elastisk stöt
    double dotproduct = (((playerxspeed - projectilexspeed) *
    (playerxpos - projectilexpos)) + ((playeryspeed - projectileyspeed) *
    (playerypos - projectileypos))) / pow((playerradius + projectileradius), 2);

    //Delar dotproduct på två för att projektil skall ge mindre bidrag till
    //hastighet än vad en krock mellan spelare (mindre massa)
    playerobject->setXSpeed(playerxspeed - ((dotproduct / 3) * (playerxpos - projectilexpos)));
    playerobject->setYSpeed(playeryspeed - ((dotproduct / 3) * (playerypos - projectileypos)));
    if (playerobject->isAlive() && !playerobject->getInvincibility())
    {
        // Dödar spelaren som blir träffad och ger den som sköt ett poäng.
        playerobject->kill();
        pointsobject.increasePoints(projectileobject->getOwner());
    }

}
