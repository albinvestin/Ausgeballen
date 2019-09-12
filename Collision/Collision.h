#ifndef COLLISION_H
#define COLLISION_H

#include "../Movingobject/Player.h"
#include "../Game/Game.h"
#include "../Obstacle/Obstacle.h"
#include "../Movingobject/Projectile.h"
#include "../Powerup/Powerup.h"
#include "../Physics/Physics.h"
#include "../Points/Points.h"
#include "../Map/Map.h"

class Collision
{
private:
    bool checkTunneling(std::shared_ptr<Movingobject>,
        std::shared_ptr<Movingobject>, int, int) noexcept;
    bool checkTunneling(std::shared_ptr<Movingobject>,
       std::shared_ptr<Obstacle>, int, bool) noexcept;

public:
    Collision() = default;
    ~Collision() = default;

    void checkCollision(std::shared_ptr<Player>, std::shared_ptr<Player>, Physics &, Game const &) noexcept;
    void checkCollision(std::shared_ptr<Player>, std::shared_ptr<Obstacle>, Physics &, Game const &) noexcept;
    bool checkCollision(std::shared_ptr<Player>, std::shared_ptr<Projectile>, Physics &, Points &, Game const &) noexcept;
    void checkCollision(std::shared_ptr<Player>, std::shared_ptr<Powerup>, Map &, Game const &) noexcept;
    bool checkCollision(std::shared_ptr<Projectile>, std::shared_ptr<Projectile>, Game const &) noexcept;
    bool checkCollision(std::shared_ptr<Projectile>, std::shared_ptr<Obstacle>, Game const &) noexcept;
};

#endif
