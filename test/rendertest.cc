#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
#include <vector>
#include "../Collision/Collision.h"
#include "../Game/Game.h"
#include "../Movingobject/Player.h"
#include "../Movingobject/Projectile.h"
#include "../Map/Map.h"
#include "../Points/Points.h"
#include "../Physics/Physics.h"
#include "../Obstacle/Obstacle.h"

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
    sf::RenderWindow startwindow {sf::VideoMode {1600, 1000}, "Ausgeballen!"};
    startwindow.clear(sf::Color::White);
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

    startwindow.draw(input);
    startwindow.display();
    sf::sleep(sf::milliseconds(1500));

    sf::Texture texture;
    if (!texture.loadFromFile("resources/ausgeballen.png"))
    {
        cout << "Macke" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(350, 150);
    startwindow.draw(sprite);
    startwindow.display();
    sf::sleep(sf::milliseconds(1500));

    Game game1;
    Map map1;
    Physics physics1;
    //Collision collision1;
    shared_ptr<Player> player1{new Player(400, 500, 10, -3, 0, 1)};
    shared_ptr<Player> player2{new Player(700, 500, 0, 10, M_PI, 2)};
    shared_ptr<Player> player3{new Player(800, 200, 3, 7, M_PI, 3)};
    shared_ptr<Player> player4{new Player(200, 200, -2, -8, M_PI, 4)};
    map1.addPlayer(player1);
    map1.addPlayer(player2);
    map1.addPlayer(player3);
    map1.addPlayer(player4);





    startwindow.clear(sf::Color::White);
    input.setString("Choose the number of ballen! (2-4)");
    centertext(input);
    startwindow.draw(input);
    startwindow.display();


    bool running1 {true};
    bool running2 {false};
    // bool running3 {false};
    while ( running1 )
    {
        // Handle events
        sf::Event event;
        while (startwindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running1 = false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num2)
                {
                    game1.setNumberOfPlayers(2);
                    running1 = false;
                    running2 = true;
                }
                if (event.key.code == sf::Keyboard::Num3)
                {
                    game1.setNumberOfPlayers(3);
                    running1 = false;
                    running2 = true;
                }
                if (event.key.code == sf::Keyboard::Num4)
                {
                    game1.setNumberOfPlayers(4);
                    running1 = false;
                    running2 = true;
                }
            }
        }
    }

    //game1.addControl(i, event.key.code);
    startwindow.clear(sf::Color::White);
    input.setString(to_string(game1.getNumberOfPlayers()));
    centertext(input);
    startwindow.draw(input);
    startwindow.display();
    sf::sleep(sf::milliseconds(1500));

    for (int i = 1; i <= game1.getNumberOfPlayers(); i++)
    {
        startwindow.clear(sf::Color::White);
        if (i == 1)
        {
            input.setColor(sf::Color::Red);
        }
        else if (i == 2)
        {
            input.setColor(sf::Color::Blue);
        }
        else if (i == 3)
        {
            input.setColor(sf::Color::Yellow);
        }
        else if (i == 4)
        {
            input.setColor(sf::Color::Green);
        }
        input.setString("Ballen" + to_string(i) + " choose your control!");
        centertext(input);
        startwindow.draw(input);
        startwindow.display();

        running2 = true;
        while (running2)
        {
            sf::Event event;
            while (startwindow.pollEvent(event))
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
                        startwindow.clear(sf::Color::White);
                        centertext(input);
                        startwindow.draw(input);
                        startwindow.display();
                        sf::sleep(sf::milliseconds(600));
                    }
                }
            }
        }
    }


        /*

            input.setString("Player1 control: ");
            startwindow.draw(input);
            startwindow.display();

            if (event.type == sf::Event::KeyPressed)
            {
                game1.addControl(i, event.key.code);
            }




        */


    return 0;
}
