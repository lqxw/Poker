#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

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
  cout << "flop 1/2, turn 1/2, river 1/2, calldown expection is "
       << getCallDownExpection(0.5, 0.5, 0.5) << endl;
  cout << "flop 1/2, turn 1/2, river 0, calldown expection is "
       << getCallDownExpection(0.5, 0.5, 0) << endl;
  cout << endl;
  cout << "flop 1/2, turn 1/2, river 1/2, fold in turn expection is "
       << getFoldInTurnExpection(0.5, 0.5, 0.5) << endl;
  cout << "flop 1/2, turn 1/2, river 0, fold in turn expection is "
       << getFoldInTurnExpection(0.5, 0.5, 0) << endl;
}
