#include "obstacles.h"

bool Obstacles::isObstacleCell(int x, int y)
{
    for (auto const &item : items)
    {
        if (x == item.x && y == item.y)
        {
            return true;
        }
    }
    return false;
}