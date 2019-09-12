#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include "../Game/Game.h"
#include "../Movingobject/Projectile.h"
#include "../Obstacle/Obstacle.h"
#include "../Powerup/Powerup.h"

class Collision;
class Player;

class Map
{
private:
    int mapwidth{};
    int mapheight{};
    bool poweruppresent{false};
    std::vector<std::shared_ptr<Player>> playerlist{};
    std::vector<std::shared_ptr<Projectile>> projectilelist{};
    std::vector<std::shared_ptr<Obstacle>> obstaclelist{};
    std::vector<std::shared_ptr<Powerup>> poweruplist{};
    int projectilespeed{30};

public:
    int getMapWidth() const noexcept;
    int getMapHeight() const noexcept;

    void updateAllPositions(Physics &, Game const &) noexcept;
    void checkAllCollisions(Collision &, Physics &, Points &, Game const &) noexcept;

    void addPlayer(std::shared_ptr<Player>) noexcept;
    void addObstacle(std::shared_ptr<Obstacle>) noexcept;
    void addProjectile(Player const &, Game const &) noexcept;
    void addPowerup(std::shared_ptr<Powerup>) noexcept;

    std::shared_ptr<Player> getPlayer(int) const noexcept;
    std::shared_ptr<Obstacle> getObstacle(int) const noexcept;
    std::shared_ptr<Projectile> getProjectile(int) const noexcept;
    std::shared_ptr<Powerup> getPowerup(int) const noexcept;
    int getProjectileSpeed() const noexcept;

    bool getPowerupPresent() const noexcept;
    void togglePowerupPresent() noexcept;

    size_t getProjectileListLength() const noexcept;
};

#endif
