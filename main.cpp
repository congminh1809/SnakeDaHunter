#include "game.h"

int main()
{
  Game game;

  while ( !game.isDone() ) {
    game.checkEvents();
    game.checkInput();
    game.update();
    game.draw();
    game.restartClock();
  }

  return 0;
}
