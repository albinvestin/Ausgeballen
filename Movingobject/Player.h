#ifndef PLAYER_H
#define PLAYER_H
#include "Movingobject.h"
#include "../Game/Game.h"
#include <cmath>

class Map;
class Physics;

class Player : public Movingobject
{
private:
    bool alive{true};
    double gundirection{};
    double gunanglespeed{M_PI/32};
    int maxspeed{30};
    int reloadtime{0};
    int recoilspeed{10};
    int inversion{1};
    bool invincibility{false};
    double quickprojectile{1};
    double slowrotation{1};
    int playerindex{};
    int deathtime{};

public:
    Player(int, int, double, double, double, int);
    ~Player() = default;

    bool isAlive() const noexcept;
    void kill() noexcept;
    void revive() noexcept;
    void shoot(Map &, Game const &) noexcept;
    void rotateGun() noexcept;
    double getGunDirection() const noexcept;
    void updatePosition(Physics &) noexcept;
    int getReloadTime() const noexcept;
    int getPlayerIndex() const noexcept;
    bool getInvincibility() const noexcept;
    void setReloadTime(int) noexcept;
    double getQuickProjectile() const noexcept;


    void switchInversion() noexcept;
    void switchInvincibility() noexcept;
    void switchQuickProjectile() noexcept;
    void switchSlowRotation() noexcept;
};

#endif
