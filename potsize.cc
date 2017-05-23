#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Always call down, folds in river if miss, can get river_win_precent pay if hits.
// The expection is two cards.
double getCallDownExpection(double flop_bet_percent, double turn_bet_percent,
                            double river_win_precent) {
  double pot = 100;
  double flop_cost = pot * flop_bet_percent;
  pot = pot + 2 * flop_cost;
  double turn_cost = pot * turn_bet_percent;
  pot = pot + 2 * turn_cost;
  double river_win = pot * river_win_precent;

  double cost = flop_cost + turn_cost;
  double win = 100 + flop_cost + turn_cost + river_win;

  double expection = cost / (win + cost);
  return expection;
}

// Folds in turn if miss, can get turn_bet_percent/river_win_precent pay if hits.
// The expection is one card.
double getFoldInTurnExpection(double flop_bet_percent, double turn_bet_percent,
                              double river_win_precent) {
  double pot = 100;
  double flop_cost = pot * flop_bet_percent;
  pot = pot + 2 * flop_cost;
  double turn_cost = pot * turn_bet_percent;
  pot = pot + 2 * turn_cost;
  double river_win = pot * river_win_precent;

  double cost = flop_cost;
  double win = 100 + flop_cost + turn_cost + river_win;

  // cost * (1 - expection) = win * expection
  double expection = cost / (cost + win);
  return expection;
}

// Check in turn if miss, can get turn_bet_percent/river_win_precent pay if hits in turn.
// The expection is one card.
double getCheckInTurnIfMissExpection(double flop_bet_percent,
                                     double turn_bet_percent,
                                     double river_win_precent) {
  double pot = 100;
  double flop_cost = pot * flop_bet_percent;
  pot = pot + 2 * flop_cost;

  // Solve the equation:
  // win = 0.5*expection*[100 + flop_cost + pot*turn_bet_percent + (pot+2*pot*turn_bet_percent)*river_win_precent] +
  //       0.5*expection*[100 + flop_cost + pot*river_win_precent]
  // cost = flop_cost;
  // expection = cost / (cost + win);

  double turn_win = pot * turn_bet_percent * expection;
  pot = pot + 2 * turn_win;
  double river_win = pot * river_win_precent;

  double cost = flop_cost;
  double win = 100 + flop_cost + turn_win + river_win;
  // working
  return 0;
  // // cost * (1 - 2*expection) = win * expection
  // double expection = cost / (2 * cost + win);
  // return expection;
}

// Check in turn not matter what, can get river_win_precent pay if hits in river.
// The expection is two cards.
double getCheckInTurnInAllCaseExpection(double flop_bet_percent,
                                        double turn_bet_percent,
                                        double river_win_precent) {
  double pot = 100;
  double flop_cost = pot * flop_bet_percent;
  pot = pot + 2 * flop_cost;

  double river_win = pot * river_win_precent;

  double cost = flop_cost;
  double win = 100 + flop_cost + river_win;

  double expection = cost / (cost + win);
  return expection;
}

int main() {
  cout << "getCallDownExpection(1/2, 1/2, 1/2) is "
       << getCallDownExpection(0.5, 0.5, 0.5) << endl;
  cout << "getCallDownExpection(1/2, 1/2, 0) is "
       << getCallDownExpection(0.5, 0.5, 0) << endl;
  cout << endl;
  cout << "getFoldInTurnExpection(1/2, 1/2, 1/2) is "
       << getFoldInTurnExpection(0.5, 0.5, 0.5) << endl;
  cout << "getFoldInTurnExpection(1/2, 1/2, 0) is "
       << getFoldInTurnExpection(0.5, 0.5, 0) << endl;
}
