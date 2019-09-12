#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "../Physics/Physics.h"

class Movingobject
{
protected:
    int xposition{};
    int yposition{};
    int lastxposition{};
    int lastyposition{};
    double xspeed{};
    double yspeed{};

public:
    Movingobject(int, int, int, int, double, double);
    virtual ~Movingobject() = default;

    int getXPosition() const noexcept;
    int getYPosition() const noexcept;
    int getLastXPosition() const noexcept;
    int getLastYPosition() const noexcept;
    double getXSpeed() const noexcept;
    double getYSpeed() const noexcept;
    void setXPosition(int) noexcept;
    void setYPosition(int) noexcept;
    void setLastXPosition(int) noexcept;
    void setLastYPosition(int) noexcept;
    void setXSpeed(double) noexcept;
    void setYSpeed(double) noexcept;
};

#endif
