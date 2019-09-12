#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <cstdlib>

#include "Collision/Collision.h"
#include "Game/Game.h"
#include "Movingobject/Player.h"
#include "Movingobject/Projectile.h"
#include "Map/Map.h"
#include "Points/Points.h"
#include "Physics/Physics.h"
#include "Obstacle/Obstacle.h"
#include "Powerup/Powerup.h"

using namespace std;
int main()
{
    Game game;
    //Initialize
    sf::RenderWindow window {sf::VideoMode {1600, 1000}, "Ausgeballen!"};
    window.clear(sf::Color::White);

    sf::Music music;
    music.openFromFile("resources/Scooter-Fire.ogg");
    music.setLoop(true);

    sf::Text input;
    sf::Font font;
    font.loadFromFile("resources/sansation.ttf");
    input.setFont(font);
    input.setCharacterSize(70);
    input.setColor(sf::Color::White);

    sf::Texture texture1;
    texture1.loadFromFile("resources/background2.png");
    sf::Sprite sprite1;
    sprite1.setTexture(texture1);
    sprite1.setPosition(0, 0);

    sf::Texture texture2;
    texture2.loadFromFile("resources/lavatexture.png");
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);
    sprite2.setPosition(0, 0);
    sf::Sprite sprite3;
    sprite3.setTexture(texture2);
    sprite3.setPosition(1300, 0);

    //Definitions
    Map world;
    Physics physics;
    Collision collision;
    shared_ptr<Player> player1{new Player(250, 250, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 0, 1)};
    shared_ptr<Player> player2{new Player(250, 750, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 0.5*M_PI, 2)};
    shared_ptr<Player> player3{new Player(750, 250, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), M_PI, 3)};
    shared_ptr<Player> player4{new Player(750, 750, floor((rand() % 5000 - rand() % 5000)/1000),
        floor((rand() % 5000 - rand() % 5000)/1000), 1.5*M_PI, 4)};


    //In game definitions
    //Powerups
    shared_ptr<Inversion> inversion{new Inversion(-10000, -10000, 10*60)};
    shared_ptr<Invincibility> invincibility{new Invincibility(-10000, -10000, 5*60)};
    shared_ptr<Quickprojectile> quickprojectile{new Quickprojectile(-10000, -10000, 10*60)};
    shared_ptr<Slowrotation> slowrotation{new Slowrotation(-10000, -10000, 7*60)};
    world.addPowerup(inversion);
    world.addPowerup(quickprojectile);
    world.addPowerup(invincibility);
    world.addPowerup(slowrotation);

    //Obstacles
    shared_ptr<Obstacle> obstacle1{new Obstacle(0, 0, 0, 960)};
    shared_ptr<Obstacle> obstacle2{new Obstacle(0, 960, 960, 960)};
    shared_ptr<Obstacle> obstacle3{new Obstacle(960, 0, 960, 960)};
    shared_ptr<Obstacle> obstacle4{new Obstacle(0, 0, 960, 0)};
    world.addObstacle(obstacle1);
    world.addObstacle(obstacle2);
    world.addObstacle(obstacle3);
    world.addObstacle(obstacle4);

    //Graphic definitions
    int centerdiff{300};

    //Ballen
    sf::CircleShape ball1 {(float)game.getPlayerRadius()};
    sf::CircleShape ball2 {(float)game.getPlayerRadius()};
    sf::CircleShape ball3 {(float)game.getPlayerRadius()};
    sf::CircleShape ball4 {(float)game.getPlayerRadius()};
    ball1.setFillColor(sf::Color::Red);
    ball2.setFillColor(sf::Color(0, 128, 255, 255));
    ball3.setFillColor(sf::Color::Green);
    ball4.setFillColor(sf::Color(255, 128, 0, 255));

    //Obstacle
    //left wall
    sf::RectangleShape wall1 {sf::Vector2f(20, 1000)};
    wall1.setFillColor(sf::Color::Black);
    wall1.setPosition(centerdiff, 0);
    //bottom wall
    sf::RectangleShape wall2 {sf::Vector2f(1000, 20)};
    wall2.setFillColor(sf::Color::Black);
    wall2.setPosition(centerdiff, 980);
    //right wall
    sf::RectangleShape wall3 {sf::Vector2f(20, 1000)};
    wall3.setFillColor(sf::Color::Black);
    wall3.setPosition(980 + centerdiff, 0);
    //upper wall
    sf::RectangleShape wall4 {sf::Vector2f(1000, 20)};
    wall4.setFillColor(sf::Color::Black);
    wall4.setPosition(centerdiff, 0);

    //Powerups
    float powerupradius{(float)game.getPowerupRadius()};
    sf::CircleShape power1 {powerupradius, 4};
    sf::CircleShape power2 {powerupradius, 4};
    sf::CircleShape power3 {powerupradius, 4};
    sf::CircleShape power4 {powerupradius, 4};
    power1.setFillColor(sf::Color::Magenta);
    power2.setFillColor(sf::Color::Magenta);
    power3.setFillColor(sf::Color::Magenta);
    power4.setFillColor(sf::Color::Magenta);


    //Print startimage
    game.printStartImage(window, input, sprite1);


    //Initialize loop: Number of players
    if (!game.initializePlayers(window, world, player1, player2, player3, player4))
    {
        return 0;
    }
    Points points{game.getNumberOfPlayers()};

    // Number of players chosen
    game.printNumberOfPlayers(window, input);


    // Initialize loop: Controller keys
    if (!game.initializeControls(window, input))
    {
        return 0;
    }

    //All init done! Countdown!
    game.countdown(window, input, music);

    //Game loop
    while (game.getRunning())
    {
        //Player colors
        game.setColor(player1, ball1);
        game.setColor(player2, ball2);
        game.setColor(player3, ball3);
        game.setColor(player4, ball4);

        //Player positions in graphics
        ball1.setPosition(player1->getXPosition() + 320 - game.getPlayerRadius(),
            player1->getYPosition() + 20 - game.getPlayerRadius());
        ball2.setPosition(player2->getXPosition() + 320 - game.getPlayerRadius(),
            player2->getYPosition() + 20 - game.getPlayerRadius());
        ball3.setPosition(player3->getXPosition() + 320 - game.getPlayerRadius(),
            player3->getYPosition() + 20 - game.getPlayerRadius());
        ball4.setPosition(player4->getXPosition() + 320 - game.getPlayerRadius(),
            player4->getYPosition() + 20 - game.getPlayerRadius());

        //Powerup positions in graphics
        power1.setPosition(inversion->getXPosition() + 320 - powerupradius,
                inversion->getYPosition() + 20 -powerupradius);
        power2.setPosition(quickprojectile->getXPosition() + 320 - powerupradius,
                quickprojectile->getYPosition() + 20 -powerupradius);
        power3.setPosition(invincibility->getXPosition() + 320 - powerupradius,
                invincibility->getYPosition() + 20 -powerupradius);
        power4.setPosition(slowrotation->getXPosition() + 320 - powerupradius,
                slowrotation->getYPosition() + 20 -powerupradius);


        game.powerupDeactivation(world);

        game.powerupSpawn(world);

        map<int, sf::Keyboard::Key> playercontrols{game.getControls()};

        game.handleKeyEvents(window, world);

        //Draw graphics
        window.clear(sf::Color::White);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(ball1);
        window.draw(ball2);

        if (game.getNumberOfPlayers() >= 3)
        {
            window.draw(ball3);
        }
        if (game.getNumberOfPlayers() == 4)
        {
            window.draw(ball4);
        }

        //Draw guns
        game.drawGuns(window, world);

        //Draw walls
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);

        //Draw powerups
        window.draw(power1);
        window.draw(power2);
        window.draw(power3);
        window.draw(power4);

        //Draw projectiles
        game.drawProjectiles(window, world);

        //Draw powerup bar
        game.drawPowerupBar(window, world);

        //Points table
        game.drawPoints(window, points, font);

        world.updateAllPositions(physics, game);
        world.checkAllCollisions(collision, physics, points, game);

        // show the newly drawn things
        window.display();

        //End game if playerpoints reach 15
        game.endGame(window, font, points);

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(50/3));
        }

    return 0;
}
