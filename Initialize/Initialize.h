#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "../Collision/Collision.h"
#include "../Game/Game.h"
#include "../Map/Map.h"
#include "../Movingobject/Player.h"
#include "../Movingobject/Projectile.h"
#include "../Physics/Physics.h"
#include "../Points/Points.h"
#include "../Powerup/Powerup.h"
#include "../Obstacle/Obstacle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <cmath>
#include <cstdlib>


class Initialize
{
private:
    sf::RenderWindow window{sf::VideoMode {1600, 1000}, "Ausgeballen!"};
    sf::Music music{};
    sf::Text input{};
    sf::Font font{};
    sf::Texture texture1{};
    sf::Texture texture2{};
    sf::Sprite sprite1{};
    sf::Sprite sprite2{};
    sf::Sprite sprite3{};

    Game game{};
    Map world{};
    Physics physics{};
    Collision collision{};

    std::shared_ptr<Player> player1{new Player(250, 250, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 0, 1)};
    std::shared_ptr<Player> player2{new Player(250, 750, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 0.5*M_PI, 2)};
    std::shared_ptr<Player> player3{new Player(750, 250, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), M_PI, 3)};
    std::shared_ptr<Player> player4{new Player(750, 750, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 1.5*M_PI, 4)};

    std::shared_ptr<Inversion> inversion{new Inversion(-10000, -10000, 10*60)};
    std::shared_ptr<Invincibility> invincibility{new Invincibility(-10000, -10000, 5*60)};
    std::shared_ptr<Quickprojectile> quickprojectile{new Quickprojectile(-10000, -10000, 10*60)};
    std::shared_ptr<Slowrotation> slowrotation{new Slowrotation(-10000, -10000, 7*60)};

    std::shared_ptr<Obstacle> obstacle1{new Obstacle(0, 0, 0, 960)};
    std::shared_ptr<Obstacle> obstacle2{new Obstacle(0, 960, 960, 960)};
    std::shared_ptr<Obstacle> obstacle3{new Obstacle(960, 0, 960, 960)};
    std::shared_ptr<Obstacle> obstacle4{new Obstacle(0, 0, 960, 0)};

    sf::CircleShape ball1 {(float)game.getPlayerRadius()};
    sf::CircleShape ball2 {(float)game.getPlayerRadius()};
    sf::CircleShape ball3 {(float)game.getPlayerRadius()};
    sf::CircleShape ball4 {(float)game.getPlayerRadius()};

    sf::RectangleShape wall1 {sf::Vector2f(20, 1000)};
    sf::RectangleShape wall2 {sf::Vector2f(1000, 20)};
    sf::RectangleShape wall3 {sf::Vector2f(20, 1000)};
    sf::RectangleShape wall4 {sf::Vector2f(1000, 20)};

    sf::CircleShape power1 {(float)game.getPowerupRadius(), 4};
    sf::CircleShape power2 {(float)game.getPowerupRadius(), 4};
    sf::CircleShape power3 {(float)game.getPowerupRadius(), 4};
    sf::CircleShape power4 {(float)game.getPowerupRadius(), 4};

    int powerupspawntime{};
    int centerdiff{300};

    std::map<int, sf::Keyboard::Key> playercontrols{};

public:
    Initialize();
    ~Initialize() = default;

    void run();

};

#endif
