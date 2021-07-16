#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void TriggerPause(); // Pausing/resuming the game depending on currenty state

private:
  Snake snake;
  SDL_Point food;

  bool _paused;    // Indicates if game is in paused state; true if game currently is paused
  bool _powerFood; // Indicates food status; true if food currently is healthy

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  void Pause();  // Pause the game
  void Resume(); // Resume the game
};

#endif