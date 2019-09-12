#ifndef PHYSICS_H
#define PHYSICS_H

#include "../Obstacle/Obstacle.h"
#include "../Points/Points.h"

#include <memory>


class Player;
class Projectile;

class Physics
{
private:
    double frictionvalue{0.12};

public:
    Physics() = default;
    ~Physics() = default;

    void friction(Player &) noexcept;
    void collision(std::shared_ptr<Player>, std::shared_ptr<Player>, int) noexcept;
    void collision(std::shared_ptr<Player>, bool) noexcept;
    void collision(std::shared_ptr<Player>, std::shared_ptr<Projectile>, Points &, int, int) noexcept;
};

#endif
