#include "Game.h"
#include <string>
#include <memory>
#include "../Map/Map.h"
#include "../Movingobject/Player.h"
#include "../Powerup/Powerup.h"

using namespace std;

void Game::setNumberOfPlayers(int count) noexcept
{
    numberofplayers = count;
}

int Game::getNumberOfPlayers() const noexcept
{
    return numberofplayers;
}

map<int, sf::Keyboard::Key> Game::getControls() const noexcept
{
    return controls;
}

int Game::getPlayerRadius() const noexcept
{
    return playerradius;
}

int Game::getProjectileRadius() const noexcept
{
    return projectileradius;
}

int Game::getPowerupRadius() const noexcept
{
    return powerupradius;
}

int Game::getEndPoints() const noexcept
{
    return endpoints;
}

void Game::addControl(int playerindex, sf::Keyboard::Key newkey) noexcept
{
    controls.insert(pair<int, sf::Keyboard::Key>(playerindex, newkey));
}

bool Game::getRunning() const noexcept
{
    return running;
}

void Game::toggleRunning() noexcept
{
    running = !running;
}

void Game::flushControls() noexcept
{
    controls.clear();
}

void Game::endGame(sf::RenderWindow & gamewindow, sf::Font const & textfont,
                    Points & pointstable) noexcept
{
    for (int i{1}; i <= numberofplayers; ++i)
    {
        if(pointstable.getPoints(i) >= getEndPoints())
        {
            gamewindow.clear(sf::Color::White);
            getScoreBoard(numberofplayers, gamewindow, textfont, pointstable);
            bool scoreloop{true};
            sf::Event event;
            while (scoreloop)
            {
                while (gamewindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        scoreloop = false;
                        toggleRunning();
                    }
                }
                gamewindow.display();
                sf::sleep(sf::milliseconds(50/3));
            }
        }
    }
}

void Game::getScoreBoard(int numberofplayers, sf::RenderWindow & gamewindow,
                    sf::Font const & textfont, Points & pointstable) noexcept
{
    int tablexpos{600};
    int tableypos{300};
    int bestscore{100};
    int pos{};
    int nextplayer{};
    int bestplayer{};
    int otherdoneplayer{};
    int looper{numberofplayers};
    sf::Text scoretext;
    scoretext.setFont(textfont);
    scoretext.setCharacterSize(50);

    while (looper > 0)
    {
        int nextscore{};
        for (int i{1}; i<= numberofplayers; ++i)
        {
            int playerpoints{pointstable.getPoints(i)};
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
        scoretext.setString(to_string(pos) + ". Player " + to_string(nextplayer)
                            + ": " + to_string(nextscore) + " pts");
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
            scoretext.setColor(sf::Color(255, 128, 0 ,255));
        }
        scoretext.setPosition(tablexpos, tableypos);
        gamewindow.draw(scoretext);
        tableypos += 60;
        --looper;
    }
}


void Game::centertext(sf::Text & input) const noexcept
{
    sf::FloatRect textRect = input.getLocalBounds();
    input.setPosition(sf::Vector2f(1600 / 2.0f, 1000 / 2.0f));
    input.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
}

bool Game::initializePlayers(sf::RenderWindow & gamewindow, Map & world,
                            shared_ptr<Player> player1, shared_ptr<Player> player2,
                            shared_ptr<Player> player3, shared_ptr<Player> player4) noexcept
{
    bool eventloop{true};
    while (eventloop)
    {
        sf::Event event;
        while (gamewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                eventloop = false;
                return false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num2)
                {
                    setNumberOfPlayers(2);
                    world.addPlayer(player1);
                    world.addPlayer(player2);
                    eventloop = false;
                }
                if (event.key.code == sf::Keyboard::Num3)
                {
                    setNumberOfPlayers(3);
                    world.addPlayer(player1);
                    world.addPlayer(player2);
                    world.addPlayer(player3);
                    eventloop = false;
                }
                if (event.key.code == sf::Keyboard::Num4)
                {
                    setNumberOfPlayers(4);
                    world.addPlayer(player1);
                    world.addPlayer(player2);
                    world.addPlayer(player3);
                    world.addPlayer(player4);
                    eventloop = false;
                }
            }
        }
    }
    return true;
}

bool Game::initializeControls(sf::RenderWindow & gamewindow, sf::Text & input) noexcept
{
    for(int i{1}; i <= numberofplayers; i++)
    {
        gamewindow.clear(sf::Color::Black);
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
        input.setString("Ballen " + to_string(i) + ", choose your control!");
        centertext(input);
        gamewindow.draw(input);
        gamewindow.display();

        bool controlloop{true};
        while (controlloop)
        {
            sf::Event event;
            while (gamewindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    controlloop = false;
                    i = 5;
                    return false;
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    // add player to world
                    addControl(i, event.key.code);
                    controlloop = false;
                }
                if ( event.type == sf::Event::TextEntered )
                {
                    if ( event.text.unicode < 0x80 ) // it's printable
                    {
                        char keyString = (char)event.text.unicode;
                        input.setString(keyString);
                        gamewindow.clear(sf::Color::Black);
                        centertext(input);
                        gamewindow.draw(input);
                        gamewindow.display();
                        sf::sleep(sf::milliseconds(600));
                    }
                }
            }
        }
    }
    return true;
}

void Game::setColor(shared_ptr<Player> currentplayer, sf::CircleShape & currentball) noexcept
{
    sf::Color color{currentball.getFillColor()};
    if(currentplayer->isAlive())
    {
        color.a = 255;
    }
    else
    {
        color.a = 75;
    }
    currentball.setFillColor(color);

    if(currentplayer->getInvincibility())
    {
        currentball.setOutlineThickness(10);
        currentball.setOutlineColor(sf::Color(145, 50, 255, 100));
    }
    else
    {
        currentball.setOutlineThickness(0);
    }
}

void Game::drawGuns(sf::RenderWindow & window, Map const & world) const noexcept
{
    for (int index{0}; index < numberofplayers; index++)
    {
        sf::RectangleShape newgun {sf::Vector2f(playerradius + 4, 0.5*projectileradius)};
        newgun.setFillColor(sf::Color::Black);
        newgun.setOrigin(0, 0.25*projectileradius);
        shared_ptr<Player> owner = world.getPlayer(index);
        newgun.setRotation(owner->getGunDirection()*180/M_PI);
        newgun.setPosition(owner->getXPosition() + 320, owner->getYPosition() + playerradius - 8);
        window.draw(newgun);
    }
}

void Game::drawProjectiles(sf::RenderWindow & window, Map const & world) const noexcept
{
    for (size_t i = 0; i < world.getProjectileListLength(); i++)
    {
        sf::CircleShape newcircle{(float)projectileradius};
        newcircle.setFillColor(sf::Color::Black);
        shared_ptr<Projectile> currentproj = world.getProjectile(i);
        newcircle.setPosition(currentproj->getXPosition() + 320 - projectileradius,
         currentproj->getYPosition() + 20 - projectileradius);
        window.draw(newcircle);
    }
}

void Game::drawPowerupBar(sf::RenderWindow & window, Map const & world) const noexcept
{
    for (int i{}; i < 4; ++i)
    {
        shared_ptr<Powerup> currentpowerup{world.getPowerup(i)};
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
            if (currentplayer->getPlayerIndex() == 1)
            {
                powerupbar.setPosition(35, 275);
            }
            if (currentplayer->getPlayerIndex() == 2)
            {
                powerupbar.setPosition(35, 675);
            }
            if (currentplayer->getPlayerIndex() == 3)
            {
                powerupbar.setPosition(1335, 275);
            }
            if (currentplayer->getPlayerIndex() == 4)
            {
                powerupbar.setPosition(1335, 675);
            }
            window.draw(powerupbar);
        }
    }
}

void Game::drawPoints(sf::RenderWindow & window, Points & points, sf::Font const & font) noexcept
{
    sf::Text text;
    for (int i{1}; i <= numberofplayers; ++i)
    {
        text.setString("Player " + to_string(i) + ": " + to_string(points.getPoints(i)));
        text.setFont(font);
        text.setCharacterSize(50);
        if (i == 1)
        {
            text.setColor(sf::Color(255, 0, 0, 255));
            text.setPosition(35, 200);
        }
        else if (i == 2)
        {
            text.setColor(sf::Color(0, 128, 255, 255));
            text.setPosition(35, 600);
        }
        else if (i == 3)
        {
            text.setColor(sf::Color(0, 255, 0, 255));
            text.setPosition(1335, 200);
        }
        else if (i == 4)
        {
            text.setColor(sf::Color(255, 128, 0, 255));
            text.setPosition(1335, 600);
        }
        window.draw(text);
    }
}

void Game::printStartImage(sf::RenderWindow & window, sf::Text & input, sf::Sprite & sprite1) const noexcept
{
    window.draw(sprite1);
    window.display();
    sf::sleep(sf::milliseconds(2250));

    window.clear(sf::Color::Black);
    input.setString("Choose the number of ballen! (2-4)");
    centertext(input);
    window.draw(input);
    window.display();
}

void Game::printNumberOfPlayers(sf::RenderWindow & window, sf::Text & input) const noexcept
{
    window.clear(sf::Color::Black);
    input.setString(to_string(getNumberOfPlayers()));
    centertext(input);
    window.draw(input);
    window.display();
    sf::sleep(sf::milliseconds(1500));
}

void Game::countdown(sf::RenderWindow & window, sf::Text & input, sf::Music & music) const noexcept
{
    input.setCharacterSize(140);
    input.setColor(sf::Color::White);
    music.setPlayingOffset(sf::milliseconds(15150));
    music.play();
    for (size_t i = 3; i != 0; i--)
    {
        window.clear(sf::Color::Black);
        input.setString(to_string(i));
        centertext(input);
        window.draw(input);
        window.display();
        sf::sleep(sf::seconds(1));
    }
    window.clear(sf::Color::Black);
    input.setString("Ausgeballen!");
    centertext(input);
    window.draw(input);
    window.display();
    sf::sleep(sf::seconds(1));
}

void Game::powerupDeactivation(Map & world) noexcept
{
    for(int i = 0; i < 4; ++i)
    {
        shared_ptr<Powerup> currentpowerup{world.getPowerup(i)};
        if (!currentpowerup->decreaseTime() && currentpowerup->getActivePlayer() != nullptr)
        {
            currentpowerup->toggleActivation();
            currentpowerup->setActivePlayer(nullptr);
        }
    }
}

void Game::powerupSpawn(Map & world) noexcept
{
    if(!world.getPowerupPresent())
    {
        ++powerupspawntime;
    }

    if(!world.getPowerupPresent() && powerupspawntime > 11*60)
    {
        powerupspawntime = 0;
        int powerupindex{(int)floor((rand() % 400000)/100000)};
        shared_ptr<Powerup> currentpowerup{world.getPowerup(powerupindex)};
        currentpowerup->setXPosition(480);
        currentpowerup->setYPosition(480);
        world.togglePowerupPresent();
    }
}

void Game::handleKeyEvents(sf::RenderWindow & window, Map & world) noexcept
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            toggleRunning();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            for(int i = 1; i <= numberofplayers; i++)
            {
                shared_ptr<Player> player = world.getPlayer(i - 1);
                if (event.key.code == controls[i])
                {
                    player->shoot(world, *this);
                }
            }
        }
    }
}
