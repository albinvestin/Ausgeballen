#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Points/Points.h"

class Map;
class Player;

class Game
{
private:
    int numberofplayers{};
    std::map<int, sf::Keyboard::Key> controls{};
    int playerradius{30};
    int projectileradius{10};
    int powerupradius{20};
    int powerupspawntime{};
    int endpoints{10};
    bool running{true};

public:
    Game() = default;
    ~Game() = default;

    void setNumberOfPlayers(int) noexcept;
    int getNumberOfPlayers() const noexcept;
    std::map<int, sf::Keyboard::Key> getControls() const noexcept;
    int getMaxSpeed() const noexcept;
    int getPlayerRadius() const noexcept;
    int getProjectileRadius() const noexcept;
    int getPowerupRadius() const noexcept;
    int getEndPoints() const noexcept;
    void addControl(int, sf::Keyboard::Key) noexcept;
    bool getRunning() const noexcept;
    void toggleRunning() noexcept;
    void flushControls() noexcept;
    void endGame(sf::RenderWindow &, sf::Font const &, Points &) noexcept;
    void getScoreBoard(int, sf::RenderWindow &, sf::Font const &, Points &) noexcept;
    void centertext(sf::Text &) const noexcept;
    bool initializePlayers(sf::RenderWindow &, Map &, std::shared_ptr<Player>,
        std::shared_ptr<Player>, std::shared_ptr<Player>, std::shared_ptr<Player>) noexcept;
    bool initializeControls(sf::RenderWindow &, sf::Text &) noexcept;
    void setColor(std::shared_ptr<Player>, sf::CircleShape &) noexcept;
    void drawGuns(sf::RenderWindow &, Map const &) const noexcept;
    void drawProjectiles(sf::RenderWindow &, Map const &) const noexcept;
    void drawPowerupBar(sf::RenderWindow &, Map const &) const noexcept;
    void drawPoints(sf::RenderWindow &, Points &, sf::Font const &) noexcept;
    void printStartImage(sf::RenderWindow &, sf::Text &, sf::Sprite &) const noexcept;
    void printNumberOfPlayers(sf::RenderWindow &, sf::Text &) const noexcept;
    void countdown(sf::RenderWindow &, sf::Text &, sf::Music &) const noexcept;
    void powerupDeactivation(Map &) noexcept;
    void powerupSpawn(Map &) noexcept;
    void handleKeyEvents(sf::RenderWindow &, Map &) noexcept;
};

#endif
