#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
#include <vector>
#include <cstdlib>
#include "../Collision/Collision.h"
#include "../Game/Game.h"
#include "../Movingobject/Player.h"
#include "../Movingobject/Projectile.h"
#include "../Map/Map.h"
#include "../Points/Points.h"
#include "../Physics/Physics.h"
#include "../Obstacle/Obstacle.h"
#include "../Powerup/Powerup.h"

using namespace std;


void centertext(sf::Text & input) noexcept
{
    sf::FloatRect textRect = input.getLocalBounds();
    input.setPosition(sf::Vector2f(1600 / 2.0f, 1000 / 2.0f));
    //input.setOrigin(textRect.width/2, textRect.height/2);
    input.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
}

int main()
{
    sf::Music music;
    if(!music.openFromFile("resources/Scooter-Fire.ogg"))
    {
        cout << "macke" << endl;
    }
    music.setLoop(true);


    sf::RenderWindow window {sf::VideoMode {1600, 1000}, "Ausgeballen!"};
    window.clear(sf::Color::White);
    sf::Text input;
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
    {
        cout << "Macke" << endl;
    }

    input.setFont(font);
    input.setString("Ausgeballen!");
    input.setCharacterSize(70);
    input.setColor(sf::Color::Black);

    centertext(input);

    window.draw(input);
    window.display();
    sf::sleep(sf::milliseconds(1500));

    sf::Texture texture;
    if (!texture.loadFromFile("resources/ausgeballen.png"))
    {
        cout << "Macke" << endl;
    }
    sf::Sprite sprite;
    window.clear(sf::Color::White);
    sprite.setTexture(texture);
    sprite.setPosition(200, 420);
    window.draw(sprite);
    window.display();
    sf::sleep(sf::milliseconds(1500));

    Game game1;
    Map map1;
    Physics physics1;
    Collision collision1;
    shared_ptr<Player> player1{new Player(250, 250, floor((rand() % 5000 - rand() % 5000)/1000), floor((rand() % 5000 - rand() % 5000)/1000), 0, 1)};
    shared_ptr<Player> player2{new Player(250, 750, floor((rand() % 5000 - rand() % 5000)/1000), floor((rand() % 5000 - rand() % 5000)/1000), 0.5 * M_PI, 2)};
    shared_ptr<Player> player3{new Player(750, 250, floor((rand() % 5000 - rand() % 5000)/1000), floor((rand() % 5000 - rand() % 5000)/1000), M_PI, 3)};
    shared_ptr<Player> player4{new Player(750, 750, floor((rand() % 5000 - rand() % 5000)/1000), floor((rand() % 5000 - rand() % 5000)/1000), 3.5 * M_PI, 4)};




    window.clear(sf::Color::White);
    input.setString("Choose the number of ballen! (2-4)");
    centertext(input);
    window.draw(input);
    window.display();


    bool running1 {true};
    bool running2 {false};
    // bool running3 {false};
    while ( running1 )
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running1 = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                map1.addPlayer(player1);
                map1.addPlayer(player2);
                if (event.key.code == sf::Keyboard::Num2)
                {
                    game1.setNumberOfPlayers(2);
                    running1 = false;
                    running2 = true;
                }
                if (event.key.code == sf::Keyboard::Num3)
                {
                    game1.setNumberOfPlayers(3);
                    map1.addPlayer(player3);
                    running1 = false;
                    running2 = true;
                }
                if (event.key.code == sf::Keyboard::Num4)
                {
                    game1.setNumberOfPlayers(4);
                    map1.addPlayer(player3);
                    map1.addPlayer(player4);
                    running1 = false;
                    running2 = true;
                }
            }
        }
    }

    //game1.addControl(i, event.key.code);
    window.clear(sf::Color::White);
    input.setString(to_string(game1.getNumberOfPlayers()));
    centertext(input);
    window.draw(input);
    window.display();
    sf::sleep(sf::milliseconds(1500));

    for (int i = 1; i <= game1.getNumberOfPlayers(); i++)
    {
        window.clear(sf::Color::White);
        if (i == 1)
        {
            input.setColor(sf::Color::Red);
        }
        else if (i == 2)
        {
            input.setColor(sf::Color(0, 128, 255, 255));
        }
        else if (i == 3)
        {
            input.setColor(sf::Color::Green);
        }
        else if (i == 4)
        {
            input.setColor(sf::Color(255, 128, 0, 255));
        }
        input.setString("Ballen " + to_string(i) + " choose your control!");
        centertext(input);
        window.draw(input);
        window.display();

        running2 = true;
        while (running2)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    running2 = false;
                    i = 5;
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    // add player to map
                    game1.addControl(i, event.key.code);
                    running2 = false;
                }
                if ( event.type == sf::Event::TextEntered )
                {
                    if ( event.text.unicode < 0x80 ) // it's printable
                    {
                        char keyString = (char)event.text.unicode;
                        input.setString(keyString);
                        window.clear(sf::Color::White);
                        centertext(input);
                        window.draw(input);
                        window.display();
                        sf::sleep(sf::milliseconds(600));
                    }
                }
            }
        }
    }




    music.setPlayingOffset(sf::seconds(18));
    music.play();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    shared_ptr<Inversion> inversion{new Inversion(-10000, -10000, 10*60)};
    shared_ptr<Invincibility> invincibility{new Invincibility(-10000, -10000, 5*60)};
    shared_ptr<Quickprojectile> quickprojectile{new Quickprojectile(-10000, -10000, 10*60)};
    shared_ptr<Slowrotation> slowrotation{new Slowrotation(-10000, -10000, 7*60)};
    map1.addPowerup(inversion);
    map1.addPowerup(quickprojectile);
    map1.addPowerup(invincibility);
    map1.addPowerup(slowrotation);

    shared_ptr<Obstacle> obstacle1{new Obstacle(0, 0, 0, 960)};
    shared_ptr<Obstacle> obstacle2{new Obstacle(0, 960, 960, 960)};
    shared_ptr<Obstacle> obstacle3{new Obstacle(960, 0, 960, 960)};
    shared_ptr<Obstacle> obstacle4{new Obstacle(0, 0, 960, 0)};
    map1.addObstacle(obstacle1);
    map1.addObstacle(obstacle2);
    map1.addObstacle(obstacle3);
    map1.addObstacle(obstacle4);
    Points points1{game1.getNumberOfPlayers()};

    int centerdiff{300};
    int playerradius = game1.getPlayerRadius();
    int projectileradius = game1.getProjectileRadius();

    //Ballen
    sf::CircleShape ball1 {(float)game1.getPlayerRadius()};
    sf::CircleShape ball2 {(float)game1.getPlayerRadius()};
    sf::CircleShape ball3 {(float)game1.getPlayerRadius()};
    sf::CircleShape ball4 {(float)game1.getPlayerRadius()};

    //Väggar
    //20 = väggarnas tjocklek, 1000 = väggarnas yttre höjd och bredd.
    //vänster
    sf::RectangleShape wall1 {sf::Vector2f(20, 1000)};
    wall1.setFillColor(sf::Color::Black);
    wall1.setPosition(centerdiff, 0);
    //botten
    sf::RectangleShape wall2 {sf::Vector2f(1000, 20)};
    wall2.setFillColor(sf::Color::Black);
    wall2.setPosition(centerdiff, 980);
    //höger
    sf::RectangleShape wall3 {sf::Vector2f(20, 1000)};
    wall3.setFillColor(sf::Color::Black);
    wall3.setPosition(980 + centerdiff, 0);
    //övre
    sf::RectangleShape wall4 {sf::Vector2f(1000, 20)};
    wall4.setFillColor(sf::Color::Black);
    wall4.setPosition(centerdiff, 0);

    //Powerups
    float powerupradius{(float)game1.getPowerupRadius()};
    sf::CircleShape power1 {powerupradius, 4};
    sf::CircleShape power2 {powerupradius, 4};
    sf::CircleShape power3 {powerupradius, 4};
    sf::CircleShape power4 {powerupradius, 4};


    power1.setFillColor(sf::Color::Magenta);
    power2.setFillColor(sf::Color::Magenta);
    power3.setFillColor(sf::Color::Magenta);
    power4.setFillColor(sf::Color::Magenta);


    map<int, sf::Keyboard::Key> playercontrols{game1.getControls()};

    sf::Texture texture2;
    if (!texture2.loadFromFile("resources/lavatexture.png"))
    {
        cout << "Macke" << endl;
    }
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);
    sprite2.setPosition(0, 0);
    sf::Sprite sprite3;
    sprite3.setTexture(texture2);
    sprite3.setPosition(1300, 0);

    int powerupspawntime{};
    while (game1.getRunning())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game1.toggleRunning();
                running1 = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == playercontrols[1])
                {
                    player1->shoot(map1, game1);
                }
                if (event.key.code == playercontrols[2])
                {
                    player2->shoot(map1, game1);
                }
                if ((game1.getNumberOfPlayers() >= 3) && event.key.code == playercontrols[3])
                {
                    player3->shoot(map1, game1);
                }
                if ((game1.getNumberOfPlayers() == 4) && event.key.code == playercontrols[4])
                {
                    player4->shoot(map1, game1);
                }
            }
        }

        // Update things
        if (player1->isAlive())
        {
            ball1.setFillColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            ball1.setFillColor(sf::Color(255, 0, 0, 75));
        }
        if (player2->isAlive())
        {
            ball2.setFillColor(sf::Color(0, 128, 255, 255));
        }
        else
        {
            ball2.setFillColor(sf::Color(0, 128, 255, 75));
        }
        if (player3->isAlive())
        {
            ball3.setFillColor(sf::Color(0, 255, 0, 255));
        }
        else
        {
            ball3.setFillColor(sf::Color(0, 255, 0, 75));
        }
        if (player4->isAlive())
        {
            ball4.setFillColor(sf::Color(255, 128, 0, 255));
        }
        else
        {
            ball4.setFillColor(sf::Color(255, 128, 0, 75));
        }

        if (player1->getInvincibility())
        {
            ball1.setOutlineThickness(10);
            ball1.setOutlineColor(sf::Color(145, 50, 255, 100));
        }
        else
        {
            ball1.setOutlineThickness(0);
        }
        if (player2->getInvincibility())
        {
            ball2.setOutlineThickness(10);
            ball2.setOutlineColor(sf::Color(145, 50, 255, 100));
        }
        else
        {
            ball2.setOutlineThickness(0);
        }
        if (player3->getInvincibility())
        {
            ball3.setOutlineThickness(10);
            ball3.setOutlineColor(sf::Color(145, 50, 255, 100));
        }
        else
        {
            ball3.setOutlineThickness(0);
        }
        if (player4->getInvincibility())
        {
            ball4.setOutlineThickness(10);
            ball4.setOutlineColor(sf::Color(145, 50, 255, 100));
        }
        else
        {
            ball4.setOutlineThickness(0);
        }


        ball1.setPosition(player1->getXPosition() + 320 - playerradius,
            player1->getYPosition() + 20 - playerradius);
        ball2.setPosition(player2->getXPosition() + 320 - playerradius,
            player2->getYPosition() + 20 - playerradius);
        ball3.setPosition(player3->getXPosition() + 320 - playerradius,
            player3->getYPosition() + 20 - playerradius);
        ball4.setPosition(player4->getXPosition() + 320 - playerradius,
            player4->getYPosition() + 20 - playerradius);

        power1.setPosition(inversion->getXPosition() + 320 - powerupradius,
                inversion->getYPosition() + 20 -powerupradius);
        power2.setPosition(quickprojectile->getXPosition() + 320 - powerupradius,
                quickprojectile->getYPosition() + 20 -powerupradius);
        power3.setPosition(invincibility->getXPosition() + 320 - powerupradius,
                invincibility->getYPosition() + 20 -powerupradius);
        power4.setPosition(slowrotation->getXPosition() + 320 - powerupradius,
                slowrotation->getYPosition() + 20 -powerupradius);

        for(int i = 0; i < 4; ++i)
        {
            shared_ptr<Powerup> currentpowerup{map1.getPowerup(i)};
            if (!currentpowerup->decreaseTime() && currentpowerup->getActivePlayer() != nullptr)
            {
                currentpowerup->toggleActivation();
                currentpowerup->setActivePlayer(nullptr);
            }
        }
        if(!map1.getPowerupPresent())
        {
            ++powerupspawntime;
        }

        if(!map1.getPowerupPresent() && powerupspawntime > 11*60)
        {
            powerupspawntime = 0;
            int powerupindex{(int)floor((rand() % 4000)/1000)};
            shared_ptr<Powerup> currentpowerup{map1.getPowerup(powerupindex)};
            currentpowerup->setXPosition(480);
            currentpowerup->setYPosition(480);
            map1.togglePowerupPresent();
        }

        // Clear screen
        window.clear(sf::Color::White);

        // Draw things
        window.draw(sprite2);
        window.draw(sprite3);

        window.draw(ball1);
        window.draw(ball2);
        if (game1.getNumberOfPlayers() >= 3)
        {
            window.draw(ball3);
        }
        if (game1.getNumberOfPlayers() == 4)
        {
            window.draw(ball4);
        }


        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(wall4);

        window.draw(power1);
        window.draw(power2);
        window.draw(power3);
        window.draw(power4);

        for (int i{}; i < 4; ++i)
        {
            shared_ptr<Powerup> currentpowerup{map1.getPowerup(i)};
            shared_ptr<Player> currentplayer = currentpowerup->getActivePlayer();
            sf::RectangleShape powerupbar {sf::Vector2f(0.4*currentpowerup->getTime(), 20)};
            if (currentplayer != nullptr)
            {
                if (i == 0)
                {
                    powerupbar.setFillColor(sf::Color(0, 102, 0, 255));
                }
                else if (i == 1)
                {
                    powerupbar.setFillColor(sf::Color(255, 153, 51, 255));
                }
                else if (i == 2)
                {
                    powerupbar.setFillColor(sf::Color(145, 50, 255, 255));
                }
                else if (i == 3)
                {
                    powerupbar.setFillColor(sf::Color(102, 178, 255, 255));
                }
                if (currentplayer == player1)
                {
                    powerupbar.setPosition(35, 275);
                }
                if (currentplayer == player2)
                {
                    powerupbar.setPosition(35, 675);
                }
                if (currentplayer == player3)
                {
                    powerupbar.setPosition(1335, 275);
                }
                if (currentplayer == player4)
                {
                    powerupbar.setPosition(1335, 675);
                }
                window.draw(powerupbar);
            }
        }

        //Poäng
        sf::Font arialfont;
        if (!arialfont.loadFromFile("resources/sansation.ttf"))
        {
            cout << "Error!" << endl; //Lägg till ordentligt fel här...
        }
        else
        {
            for (int i{1}; i <= game1.getNumberOfPlayers(); ++i)
            {
                sf::Text text1;
                text1.setString("Player " + to_string(i) + ": " + to_string(points1.getPoints(i)));
                text1.setFont(arialfont);
                text1.setCharacterSize(50);
                if (i == 1)
                {
                    text1.setColor(sf::Color(255, 0, 0, 255));
                    text1.setPosition(35, 200);
                }
                else if (i == 2)
                {
                    text1.setColor(sf::Color(0, 128, 255, 255));
                    text1.setPosition(35, 600);
                }
                else if (i == 3)
                {
                    text1.setColor(sf::Color(0, 255, 0, 255));
                    text1.setPosition(1335, 200);
                }
                else if (i == 4)
                {
                    text1.setColor(sf::Color(255, 128, 0, 255));
                    text1.setPosition(1335, 600);
                }
                window.draw(text1);
            }
        }

//Gun loop
        for (int index{0}; index < game1.getNumberOfPlayers(); index++)
        {
            sf::RectangleShape newgun {sf::Vector2f(playerradius + 4, 0.5*game1.getProjectileRadius())};
            newgun.setFillColor(sf::Color::Black);
            newgun.setOrigin(0, 0.25*game1.getProjectileRadius());
            shared_ptr<Player> owner = map1.getPlayer(index);
            newgun.setRotation(owner->getGunDirection()*180/M_PI);
            newgun.setPosition(owner->getXPosition() + 320, owner->getYPosition() + playerradius - 8);
            window.draw(newgun);
        }

//Projectile loop
        for (size_t i = 0; i < map1.getProjectileListLength(); i++)
        {
            sf::CircleShape newcircle{(float)projectileradius};
            newcircle.setFillColor(sf::Color::Black);
            shared_ptr<Projectile> currentproj = map1.getProjectile(i);
            newcircle.setPosition(currentproj->getXPosition() + 320 - projectileradius,
             currentproj->getYPosition() + 20 - projectileradius);
            window.draw(newcircle);
        }

        map1.updateAllPositions(physics1, game1);
        map1.checkAllCollisions(collision1, physics1, points1, game1);

        // show the newly drawn things
        window.display();

        //End game if playerpoints reach 15
        for(int i = 1; i <= game1.getNumberOfPlayers(); ++i)
        {
            if(points1.getPoints(i) >= game1.getEndPoints())
            {
                window.clear(sf::Color::White);
                sf::Font scorefont;
                if (!scorefont.loadFromFile("resources/sansation.ttf"))
                {
                    cout << "Error!" << endl; //Lägg till ordentligt fel här...
                }
                else
                    {
                        int numberofplayers{game1.getNumberOfPlayers()};
                        int tablexpos{200};
                        int tableypos{200};
                        int bestscore{100};
                        int pos{};
                        int nextplayer{};
                        int bestplayer{};
                        int otherdoneplayer{};
                        int t{numberofplayers};
                        sf::Text scoretext;
                        while (t > 0)
                        {
                            int nextscore{};
                            for (int i{1}; i <= numberofplayers; ++i)
                            {
                                int playerpoints{points1.getPoints(i)};
                                if ((playerpoints >= nextscore) &&
                                    (playerpoints <= bestscore) &&
                                    (i != bestplayer) &&
                                    (i != otherdoneplayer))
                                    {
                                        nextscore = playerpoints;
                                        nextplayer = i;
                                    }
                                }
                                ++pos;
                                otherdoneplayer = bestplayer;
                                bestscore = nextscore;
                                bestplayer = nextplayer;
                                scoretext.setString(to_string(pos) + ". Player " + to_string(nextplayer) + ": " + to_string(nextscore) + " pts");
                                scoretext.setFont(scorefont);
                                scoretext.setCharacterSize(50);
                                if (nextplayer == 1)
                                {
                                    scoretext.setColor(sf::Color::Red);
                                }
                                else if (nextplayer == 2)
                                {
                                    scoretext.setColor(sf::Color(0, 128, 255, 255));
                                }
                                else if (nextplayer == 3)
                                {
                                    scoretext.setColor(sf::Color::Green);
                                }
                                else if (nextplayer == 4)
                                {
                                    scoretext.setColor(sf::Color(255, 128, 0, 255));
                                }
                                scoretext.setPosition(tablexpos, tableypos);;
                                window.draw(scoretext);
                                tableypos += 60;
                                --t;
                            }
                        }
                        running1 = true;
                        while (running1)
                        {
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    running1 = false;
                                    game1.toggleRunning();
                                }
                            }
                            window.display();
                            sf::sleep(sf::milliseconds(50/3));
                        }
                }
            }

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(50/3));
    }
return 0;
}
