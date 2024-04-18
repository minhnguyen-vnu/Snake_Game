#include "game.hpp"

struct InfinityMap{
  int virtualRow[35];
  int virtualCol[35];
  int actualRow[35];
  int actualCol[35];

  void init();
  void Move(int dir);
};
