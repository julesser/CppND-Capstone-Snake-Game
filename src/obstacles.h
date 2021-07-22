
#ifndef OBSTACLES_H
#define OBSTACLES_H
#include "SDL.h"
#include <vector>
#include "snake.h"

class Obstacles
{
public:
    Obstacles(int num_of_obstacles) : number_of_obstacles(num_of_obstacles) {}
    bool isObstacleCell(int x, int y); // Indicates if current cell is an obstacle
    std::vector<SDL_Point> items;      // Vector of obstacles
    int number_of_obstacles;           // Obstacle count
};
#endif