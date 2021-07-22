#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Ask the user to enter number of obstacles
  int num_of_obstacles;
  std::cout << "WELCOME TO THE SNAKE GAME!" << std::endl;
  std::cout << "Please enter the number of obstacles to appear: " << std::endl;
  std::cin >> num_of_obstacles;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, num_of_obstacles);
  Controller controller;
  Game game(kGridWidth, kGridHeight, num_of_obstacles);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}