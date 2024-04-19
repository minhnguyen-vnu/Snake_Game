#pragma once
#include "admin.hpp"

struct Highscore{
  int score[7];
  void update(int type, int score);
};
