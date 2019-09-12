#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Movingobject.h"

class Projectile : public Movingobject
{
private:
    int owner{};

public:
    Projectile(int, int, double, double, int);
    ~Projectile() = default;

    int getOwner() const noexcept;
    void updatePosition() noexcept;
};

#endif
