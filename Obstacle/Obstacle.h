#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
private:
    int xstart{};
    int ystart{};
    int xend{};
    int yend{};

public:
    Obstacle(int, int, int, int);
    ~Obstacle() = default;

    int getXStart() const noexcept;
    int getXEnd() const noexcept;
    int getYStart() const noexcept;
    int getYEnd() const noexcept;
};

#endif
