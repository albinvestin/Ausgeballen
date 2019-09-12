#include <iostream>
//#include <iomanip>
//#include <cmath>
#include "../Movingobject/Player.h"
#include "../Collision/Collision.h"
#include "../Game/Game.h"
#include "../Obstacle/Obstacle.h"
#include "../Movingobject/Projectile.h"
#include "../Physics/Physics.h"
#include "../Map/Map.h"
#include <memory>
//#include "../Points/Points.h

using namespace std;

int main()
{
    Collision collisionobject{};
    Game* gameobject = new Game{};
    Physics* physicsobject = new Physics{};
    /* TEST1 - Superbra!

    Player* player1 = new Player{0, 0, 1, 1, 0};
    Player* player2 = new Player{5, 5, -1, -1, 0};

    for (int i = 0; i < 20; i++)
    {
        collisionobject.checkCollision(player1, player2, gameobject);
        player1->updatePosition();
        player2->updatePosition();
    }
    */

    /* TEST2 - Superbra2!

    Player* player1 = new Player{0, 0, 1, 1, 0};
    Obstacle* obstacle1 = new Obstacle{10, -10, 10, 10};
    Obstacle* obstacle2 = new Obstacle{-10 , 10, 10, 10};

    for (int i = 0; i < 25; i++)
    {
        collisionobject.checkCollision(player1, obstacle1, gameobject);
        collisionobject.checkCollision(player1, obstacle2, gameobject);
        player1->updatePosition();
    }
    */
/*
    //TEST3 - 3 Kanonbra!!

    Player* player1 = new Player{0, 0, 1, 1, 0};
    Projectile* projectile1 = new Projectile{4, 4, 0, 0, 2};

    for (int i = 0; i < 25; i++)
    {
        collisionobject.checkCollision(player1, projectile1, gameobject);
        player1->updatePosition();
        projectile1->updatePosition();
    }
*/

    //TEST 4 Physics test - Bra! :)
    shared_ptr<Player> player1{new Player(0, 0, 70, 0, 0, 1)};
    //shared_ptr<Player> player2{new Player(101, 0, 0, 0, 0, 2)};
    shared_ptr<Obstacle> obstacle1{new Obstacle(200, -60, 200, 60)};
    // shared_ptr<Obstacle> obstacle2{new Obstacle(-60, 60, 60, 60)};
    shared_ptr<Obstacle> obstacle3{new Obstacle(0, -60, 0, 60)};
    // shared_ptr<Obstacle> obstacle4{new Obstacle(-60, -60, 60, -60)};



    int t{20};

    cout << '\n' << "While-loopen..." << endl;
    while(t > 0)
    {
        cout << "Frame: " << (20 - t) << endl;
        cout << "Player 1 Position: (" << player1->getXPosition() << ", " << player1->getYPosition() << ")" << endl;
        //cout << "Player 2 Position: (" << player2->getXPosition() << ", " << player2->getYPosition() << ")" << endl;
        cout << "Player 1 Speed: (" << player1->getXSpeed() << ", " << player1->getYSpeed() << ")" << endl;
        //cout << "Player 2 Speed: (" << player2->getXSpeed() << ", " << player2->getYSpeed() << ")" << "\n" << endl;
        t--;
        // collisionobject.checkCollision(player1, obstacle1, physicsobject, gameobject);
        // collisionobject.checkCollision(player1, obstacle2, physicsobject, gameobject);
        // collisionobject.checkCollision(player1, obstacle3, physicsobject, gameobject);
        // collisionobject.checkCollision(player1, obstacle4, physicsobject, gameobject);
        player1->updatePosition(physicsobject);
        //player2->updatePosition(physicsobject);

        //collisionobject.checkCollision(player1, player2, physicsobject, gameobject);
        collisionobject.checkCollision(player1, obstacle1, physicsobject, gameobject);
        collisionobject.checkCollision(player1, obstacle3, physicsobject, gameobject);

    }


    return 0;
}
