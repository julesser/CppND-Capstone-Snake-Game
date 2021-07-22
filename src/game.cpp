#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int num_of_obstacles)
    : snake(grid_width, grid_height),
      obstacles(num_of_obstacles),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
  PlaceFood();
  PlaceObstacles();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, *this);
    Update();
    renderer.Render(snake, food, _powerFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

bool Game::isOccupiedCell(int x, int y)
{
  return snake.SnakeCell(x, y) || obstacles.isObstacleCell(x, y);
}

void Game::PlaceObstacles()
{
  int x, y;
  int num_obstacles = 0;

  while (num_obstacles < obstacles.number_of_obstacles)
  {
    while (true)
    {
      SDL_Point obstacle;
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a snake item before placing
      // food.
      if (!isOccupiedCell(x, y))
      {
        obstacle.x = x;
        obstacle.y = y;
        obstacles.items.push_back(obstacle);
        num_obstacles++;
        break;
      }
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);

    // Set probability of power food to 25%
    _powerFood = (rand() % 100) < 75;

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!isOccupiedCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

bool Game::isSnakeOnObstacle()
{
  for (auto const &item : obstacles.items)
  {
    if (snake.SnakeCell(item.x, item.y))
      return true;
  }
  return false;
}

void Game::Update()
{
  if (this->_paused == true)
    return;
  if (isSnakeOnObstacle())
  {
    snake.alive = false;
  }
  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake
    snake.GrowBody();
    // Increase speed only when not powerFood
    if (!_powerFood)
    {
      snake.speed += 0.02;
    }
  }
}

void Game::TriggerPause()
{
  // If game is paused, resume it, otherwise pause the game
  this->_paused ? Resume() : Pause();
}

void Game::Pause()
{
  this->_paused = true;
}

void Game::Resume()
{
  this->_paused = false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }