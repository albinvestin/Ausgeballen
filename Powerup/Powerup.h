#ifndef POWERUP_H
#define POWERUP_H

#include "../Movingobject/Player.h"
#include <memory>

class Powerup
{
protected:
    int xposition{};
    int yposition{};
    int poweruptime{};
    int duration{};
    std::shared_ptr<Player> activeplayer{};

public:
    Powerup(int, int, int);
    ~Powerup() = default;

    int getXPosition() const noexcept;
    int getYPosition() const noexcept;
    void setXPosition(int) noexcept;
    void setYPosition(int) noexcept;
    bool decreaseTime() noexcept;  //return true if t>0
    void setTime() noexcept;
    int getTime() const noexcept;
    std::shared_ptr<Player> getActivePlayer() const noexcept;
    void setActivePlayer(std::shared_ptr<Player>) noexcept;

    virtual void toggleActivation() noexcept = 0;
};



class Inversion : public Powerup
{
public:
    Inversion(int, int, int);
    void toggleActivation() noexcept override;
};



class Invincibility : public Powerup
{
public:
    Invincibility(int, int, int);
    void toggleActivation() noexcept override;
};



class Quickprojectile : public Powerup
{
public:
    Quickprojectile(int, int, int);
    void toggleActivation() noexcept override;
};



class Slowrotation : public Powerup
{
public:
    Slowrotation(int, int, int);
    void toggleActivation() noexcept override;
};



#endif
