#include "texas.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

vector<vector<Card>> reasonableHandRange = {
    // pocket
    {Card("2*"), Card("2*")},
    {Card("3*"), Card("3*")},
    {Card("4*"), Card("4*")},
    {Card("5*"), Card("5*")},
    {Card("6*"), Card("6*")},
    {Card("7*"), Card("7*")},
    {Card("8*"), Card("8*")},
    {Card("9*"), Card("9*")},
    {Card("T*"), Card("T*")},
    {Card("J*"), Card("J*")},
    {Card("Q*"), Card("Q*")},
    {Card("K*"), Card("K*")},
    {Card("A*"), Card("A*")},
    // small suited connector

    {Card("4h"), Card("5h")},
    {Card("4s"), Card("5s")},
    {Card("4d"), Card("5d")},
    {Card("4c"), Card("5c")},

    {Card("5h"), Card("6h")},
    {Card("5s"), Card("6s")},
    {Card("5d"), Card("6d")},
    {Card("5c"), Card("6c")},

    {Card("6h"), Card("7h")},
    {Card("6s"), Card("7s")},
    {Card("6d"), Card("7d")},
    {Card("6c"), Card("7c")},

    {Card("7h"), Card("8h")},
    {Card("7s"), Card("8s")},
    {Card("7d"), Card("8d")},
    {Card("7c"), Card("8c")},

    {Card("8h"), Card("9h")},
    {Card("8s"), Card("9s")},
    {Card("8d"), Card("9d")},
    {Card("8c"), Card("9c")},

    {Card("9h"), Card("Th")},
    {Card("9s"), Card("Ts")},
    {Card("9d"), Card("Td")},
    {Card("9c"), Card("Tc")},

    {Card("Th"), Card("Jh")},
    {Card("Ts"), Card("Js")},
    {Card("Td"), Card("Jd")},
    {Card("Tc"), Card("Jc")},

    {Card("Jh"), Card("Qh")},
    {Card("Js"), Card("Qs")},
    {Card("Jd"), Card("Qd")},
    {Card("Jc"), Card("Qc")},

    // A high suited
    {Card("Ah"), Card("2h")},
    {Card("As"), Card("2s")},
    {Card("Ad"), Card("2d")},
    {Card("Ac"), Card("2c")},

    {Card("Ah"), Card("3h")},
    {Card("As"), Card("3s")},
    {Card("Ad"), Card("3d")},
    {Card("Ac"), Card("3c")},

    {Card("Ah"), Card("4h")},
    {Card("As"), Card("4s")},
    {Card("Ad"), Card("4d")},
    {Card("Ac"), Card("4c")},

    {Card("Ah"), Card("5h")},
    {Card("As"), Card("5s")},
    {Card("Ad"), Card("5d")},
    {Card("Ac"), Card("5c")},

    {Card("Ah"), Card("6h")},
    {Card("As"), Card("6s")},
    {Card("Ad"), Card("6d")},
    {Card("Ac"), Card("6c")},

    {Card("Ah"), Card("7h")},
    {Card("As"), Card("7s")},
    {Card("Ad"), Card("7d")},
    {Card("Ac"), Card("7c")},

    {Card("Ah"), Card("8h")},
    {Card("As"), Card("8s")},
    {Card("Ad"), Card("8d")},
    {Card("Ac"), Card("8c")},

    {Card("Ah"), Card("9h")},
    {Card("As"), Card("9s")},
    {Card("Ad"), Card("9d")},
    {Card("Ac"), Card("9c")},

    {Card("Ah"), Card("Th")},
    {Card("As"), Card("Ts")},
    {Card("Ad"), Card("Td")},
    {Card("Ac"), Card("Tc")},

    {Card("Ah"), Card("Jh")},
    {Card("As"), Card("Js")},
    {Card("Ad"), Card("Jd")},
    {Card("Ac"), Card("Jc")},

    {Card("Ah"), Card("Qh")},
    {Card("As"), Card("Qs")},
    {Card("Ad"), Card("Qd")},
    {Card("Ac"), Card("Qc")},

    {Card("Ah"), Card("Kh")},
    {Card("As"), Card("Ks")},
    {Card("Ad"), Card("Kd")},
    {Card("Ac"), Card("Kc")},

    // high cards
    {Card("T*"), Card("J*")},
    {Card("T*"), Card("Q*")},
    {Card("T*"), Card("K*")},
    {Card("T*"), Card("A*")},

    {Card("J*"), Card("Q*")},
    {Card("J*"), Card("K*")},
    {Card("J*"), Card("A*")},

    {Card("Q*"), Card("K*")},
    {Card("Q*"), Card("A*")},

    {Card("K*"), Card("A*")},
};

vector<vector<Card>> allInHandRange = {
    {Card("A*"), Card("A*")},
    {Card("K*"), Card("K*")},
    {Card("Q*"), Card("Q*")},
    {Card("A*"), Card("K*")},

    // 33% JJ (hs, hd, hc, sd, sc, dc)
    {Card("Jh"), Card("Js")},
    {Card("Jh"), Card("Jd")},
};

vector<vector<Card>> threeBetHandRange = {
    // clang-format off
    {Card("A*"), Card("A*")},
    {Card("A*"), Card("K*")},
    {Card("A*"), Card("Q*")},
    {Card("A*"), Card("J*")},
    {Card("K*"), Card("K*")},
    {Card("Q*"), Card("Q*")},
    {Card("J*"), Card("J*")},
    // clang-format on
};

vector<vector<Card>> anyRange = {{Card("*"), Card("*")}};

// Probability that get a playable hand.
void prob_get_playable_hand() {
  cout << "Probability that get a playable hand: "
       << 100 * getHandProb(reasonableHandRange) << '%' << endl;
}

// Pocket hits a set on flop.
void prob_hit_set_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("7d")};
  vector<vector<Card>> patterns = {
      {Card("7*"), Card("*"), Card("*")},
  };
  cout << "Pocket hits a set on flop: " << 100 * getProb(patterns, myHand)
       << '%' << endl;
}

// Any card hits a pair on flop.
void prob_any_card_hits_pair_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("7*"), Card("*"), Card("*")},  // 7 hits
      {Card("8*"), Card("*"), Card("*")},  // 8 hits
  };
  cout << "Any card hits a pair on flop: " << 100 * getProb(patterns, myHand)
       << '%' << endl;
}

// High card hits a pair on flop.
void prob_high_card_hits_pair_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("8*"), Card("*"), Card("*")},
  };
  cout << "High card hits a pair on flop: " << 100 * getProb(patterns, myHand)
       << '%' << endl;
}

// Two different cards hit two pairs or trips on flop.
void prob_hits_two_pairs_or_trips_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("7*"), Card("8*"), Card("*")},  // two pair
      {Card("7*"), Card("7*"), Card("*")},  // trips
      {Card("8*"), Card("8*"), Card("*")},  // trips
  };
  cout << "Two different cards hit two pairs or trips on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Suited connector hits a straight or flush draw on flop.
void prob_suited_connector_hits_straight_or_flush_draw_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("5*"), Card("6*"), Card("*")},
      {Card("6*"), Card("9*"), Card("*")},
      {Card("9*"), Card("10*"), Card("*")},
      {Card("*s"), Card("*s"), Card("*")},
  };
  cout << "Suited connector hits open end straight/flush draw on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Suited connector hits a flush draw on flop.
void prob_suited_connector_hits_flush_draw_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("*s"), Card("*s"), Card("*")},
  };
  cout << "Suited connector hits flush draw on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Suited connector hits a straight draw on flop.
void prob_suited_connector_hits_straight_draw_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("5*"), Card("6*"), Card("*")},
      {Card("6*"), Card("9*"), Card("*")},
      {Card("9*"), Card("10*"), Card("*")},
  };
  cout << "Suited connector hits open end straight draw on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Suited connector hits a straight/flush/two pair/trips on flop.
void prob_suited_connector_hits_two_pairs_trips_straight_flush_on_flop() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("4*"), Card("5*"), Card("6*")},  // straight
      {Card("5*"), Card("6*"), Card("9*")},  // straight
      {Card("6*"), Card("9*"), Card("T*")},  // straight
      {Card("9*"), Card("T*"), Card("J*")},  // straight
      {Card("*s"), Card("*s"), Card("*s")},  // flush
      {Card("7*"), Card("8*"), Card("*")},   // two pair
      {Card("7*"), Card("7*"), Card("*")},   // trips
      {Card("8*"), Card("8*"), Card("*")},   // trips
  };
  cout << "Suited connector hits straight/flush/two pair/trips on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Suited connector hits a straight or flush on river.
void prob_suited_connector_hits_straight_or_flush_on_river() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("4*"), Card("5*"), Card("6*"), Card("*"), Card("*")},  // straight
      {Card("5*"), Card("6*"), Card("9*"), Card("*"), Card("*")},  // straight
      {Card("6*"), Card("9*"), Card("T*"), Card("*"), Card("*")},  // straight
      {Card("9*"), Card("T*"), Card("J*"), Card("*"), Card("*")},  // straight
      {Card("*s"), Card("*s"), Card("*s"), Card("*ns"), Card("*ns")},  // flush
  };
  cout << "Suited connector hits straight/flush on river: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Two cards hit two pair or trips on river.
void prob_hits_two_pairs_or_trips_on_river() {
  vector<Card> myHand = {Card("7s"), Card("8s")};
  vector<vector<Card>> patterns = {
      {Card("7*"), Card("8*"), Card("*"), Card("*"), Card("*")},  // two pair
      {Card("7*"), Card("7*"), Card("*"), Card("*"), Card("*")},  // trips
      {Card("8*"), Card("8*"), Card("*"), Card("*"), Card("*")},  // trips
  };
  cout << "Two different cards hit two pairs or trips on river: "
       << 100 * getProb(patterns, myHand) << '%' << endl;
}

// Pocket hits a set on river.
void prob_hit_set_on_river() {
  vector<Card> myHand = {Card("7s"), Card("7d")};
  vector<vector<Card>> patterns = {
      {Card("7*"), Card("*"), Card("*"), Card("*"), Card("*")},
  };
  cout << "Pocket hits a set on river: " << 100 * getProb(patterns, myHand)
       << '%' << endl;
}

// Probability that get AA.
void prob_get_AA() {
  vector<vector<Card>> patterns = {{Card("A*"), Card("A*")}};
  cout << "Probability that get AA: " << 100 * getHandProb(patterns) << '%'
       << endl;
}

// Probability that get AK.
void prob_get_AK() {
  vector<vector<Card>> patterns = {{Card("A*"), Card("K*")}};
  cout << "Probability that get AK: " << 100 * getHandProb(patterns) << '%'
       << endl;
}

// Probability that other player goes all in with AA, when I have KK.
void prob_other_has_AA_when_I_have_KK() {
  vector<vector<Card>> patterns = {{Card("A*"), Card("A*")}};
  vector<Card> myHand = {Card("Ks"), Card("Kh")};
  cout << "Probability that other player goes all in with AA, when I have KK: "
       << 100 * getHandProb(patterns, allInHandRange, myHand) << '%' << endl;
}

// Probability that other player goes all in with AA, when I have AK.
void prob_other_has_AA_when_I_have_AK() {
  vector<vector<Card>> othersHand = {{Card("A*"), Card("A*")}};
  vector<Card> myHand = {Card("As"), Card("Kh")};
  cout << "Probability that other player goes all in with AA, when I have AK: "
       << 100 * getHandProb(othersHand, allInHandRange, myHand) << '%' << endl;
}

// Probability that other player hits trips on flop.
void prob_other_hits_trips_on_flop() {
  vector<vector<Card>> othersHand = {{Card("9*"), Card("*")}};
  vector<Card> board = {
      {Card("9s"), Card("9d"), Card("2s"),  // flop
       Card("As"), Card("Kh")}              // my hand
  };
  cout << "Probability that other player hits trips on flop: "
       << 100 * getHandProb(othersHand, reasonableHandRange, board) << '%'
       << endl;
}

int main() {
  srand(time(NULL));

  // prob_get_playable_hand();
  // prob_hit_set_on_flop();
  // prob_any_card_hits_pair_on_flop();
  // prob_high_card_hits_pair_on_flop();
  // prob_hits_two_pairs_or_trips_on_flop();
  // prob_suited_connector_hits_straight_or_flush_draw_on_flop();
  // prob_suited_connector_hits_flush_draw_on_flop();
  // prob_suited_connector_hits_straight_draw_on_flop();
  // prob_suited_connector_hits_two_pairs_trips_straight_flush_on_flop();
  // prob_suited_connector_hits_straight_or_flush_on_river();
  // prob_hits_two_pairs_or_trips_on_river();
  // prob_hit_set_on_river();
  // prob_get_AA();
  prob_get_AK();
  // prob_other_has_AA_when_I_have_KK();
  // prob_other_has_AA_when_I_have_AK();
  // prob_other_hits_trips_on_flop();
}
