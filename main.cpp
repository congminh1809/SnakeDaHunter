#include "game.h"

int main()
{
  Game game;

  while ( !game.isDone() ) {
    game.update();
    game.draw();
  }

  return 0;
}
