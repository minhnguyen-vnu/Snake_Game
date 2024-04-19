#include "Highscore.hpp"

void Highscore::update(int type, int point){
  ifstream input("Highscore.txt");

  for(int i = 1; i <= 5; ++i) input >> score[i];
  input.close();
  score[type] = max(score[type], point);
  ofstream output("Highscore.txt");
  for(int i = 1; i <= 5; ++i) output << score[i] << '\n';

  output.close();
}
