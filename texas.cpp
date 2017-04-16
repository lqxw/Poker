#include "texas.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace {
int char2num(char c) {
  switch (c) {
    case '*':
      return 0;
    case 'A':
      return 1;
    case 'K':
      return 13;
    case 'Q':
      return 12;
    case 'J':
      return 11;
    case 'T':
      return 10;
    default:
      return int(c) - '0';
  }
}

char num2char(int num) {
  switch (num) {
    case 1:
      return 'A';
    case 13:
      return 'K';
    case 12:
      return 'Q';
    case 11:
      return 'J';
    case 10:
      return 'T';
    default:
      return char(num + '0');
  }
}

int vecFind(const vector<Card>& vec, Card card) {
  for (unsigned int i = 0; i < vec.size(); i++) {
    if (vec[i] == card) return i;
  }
  return -1;
}

void vecErase(vector<Card>& vec, int index) { vec.erase(vec.begin() + index); }

void vecPrint(const vector<Card>& vec) {
  for (const Card& card : vec) card.print();
  cout << endl;
}

// pattern much be ordered by strictness
int isMatch(vector<Card> pattern, const vector<Card>& given) {
  for (Card card : given) {
    int index = vecFind(pattern, card);
    if (index == -1) return false;
    vecErase(pattern, index);
  }
  return true;
}

int isMatch(const vector<vector<Card>>& patterns, vector<Card> given) {
  for (auto pattern : patterns) {
    if (isMatch(pattern, given) == true) return true;
  }
  return false;
}

vector<Card> generateRandomCards(const vector<Card>& existingCards,
                                 int size = 5) {
  vector<Card> ret;
  for (int i = 0; i < size; i++) {
    while (1) {
      Card current(rand() % 52 + 4);
      if (vecFind(ret, current) == -1 &&
          vecFind(existingCards, current) == -1) {
        ret.push_back(current);
        break;
      }
    }
  }
  // vecPrint(ret);
  return ret;
}

}  // namespace

Card::Card(int num) {
  value = num / 4;
  int suitvalue = num % 4;
  if (suitvalue == 0) suit = "h";
  if (suitvalue == 1) suit = "s";
  if (suitvalue == 2) suit = "d";
  if (suitvalue == 3) suit = "c";
}

Card::Card(string s) {
  if (s == "*") {
    value = 0;
    suit = "*";
  } else {
    value = char2num(s[0]);
    suit = s.substr(1);
  }
}

Card::Card(int n, string s) {
  value = n;
  suit = s;
}

bool Card::operator==(const Card& other) const {
  return checkNum(this->value, other.value) and
         checkSuit(this->suit, other.suit);
}
void Card::print() const { cout << num2char(value) << suit << " "; }

bool Card::checkNum(int a, int b) const {
  if (a == 0 || b == 0) return true;
  if (a > 0 && b > 0) return a == b;
  if (a < 0 && b < 0) return true;
  return a + b;
}

bool Card::checkSuit(string a, string b) const {
  if (a == "*" || b == "*") return true;
  if (a.length() == 1 && b.length() == 1) return a == b;
  if (a.length() == 2 && b.length() == 2) return true;
  if (a.length() == 2) return a[1] != b[0];  // nx
  if (b.length() == 2) return a[0] != b[1];  // nx
  assert(0);
  return 0;
}

// Public function
float getHandProb(const vector<Card>& handPatterns,
                  const vector<Card>& existingCards) {
  int success = 0;
  int fail = 0;
  for (int i = 0; i < RUNTIMES; i++) {
    vector<Card> currentHand = generateRandomCards(existingCards, 2);
    if (isMatch(handPatterns, currentHand))
      success++;
    else
      fail++;
  }
  return (float)success / (float)(fail + success);
}

// Public function
float getHandProb(const vector<vector<Card>>& handPatterns,
                  const vector<Card>& existingCards) {
  int success = 0;
  int fail = 0;
  for (int i = 0; i < RUNTIMES; i++) {
    vector<Card> currentHand = generateRandomCards(existingCards, 2);
    if (isMatch(handPatterns, currentHand))
      success++;
    else
      fail++;
  }
  return (float)success / (float)(fail + success);
}

// Public function
float getHandProb(const vector<vector<Card>>& specificHandPatterns,
                  const vector<vector<Card>>& handRanges,
                  const vector<Card>& existingCards) {
  int success = 0;
  int fail = 0;
  for (int i = 0; i < RUNTIMES * 10; i++) {
    vector<Card> currentHand = generateRandomCards(existingCards, 2);
    if (!isMatch(handRanges, currentHand)) continue;
    if (isMatch(specificHandPatterns, currentHand))
      success++;
    else
      fail++;
  }
  return (float)success / (float)(fail + success);
}

// Public function
float getProb(const vector<Card>& boardPatterns,
              const vector<Card>& existingCards) {
  int success = 0;
  int fail = 0;
  for (int i = 0; i < RUNTIMES; i++) {
    vector<Card> currentBoard =
        generateRandomCards(existingCards, boardPatterns.size());
    if (isMatch(boardPatterns, currentBoard))
      success++;
    else
      fail++;
  }
  return (float)success / (float)(fail + success);
}

// Public function
float getProb(const vector<vector<Card>>& boardPatterns,
              const vector<Card>& existingCards) {
  int success = 0;
  int fail = 0;
  for (int i = 0; i < RUNTIMES; i++) {
    vector<Card> currentBoard =
        generateRandomCards(existingCards, boardPatterns[0].size());
    if (isMatch(boardPatterns, currentBoard))
      success++;
    else
      fail++;
  }
  return (float)success / (float)(fail + success);
}

int main() {
  srand(time(NULL));
  vector<vector<Card>> patterns;
  vector<Card> myHand;              // Exact hand
  vector<vector<Card>> othersHand;  // Pattern
  vector<Card> board;

  // Test
  // Suited connector hits a straight draw or flush draw on flop.
  myHand = {Card("7s"), Card("8s")};
  patterns = {
      {Card("5*"), Card("6*"), Card("*")},
      {Card("6*"), Card("9*"), Card("*")},
      {Card("9*"), Card("10*"), Card("*")},
      {Card("*s"), Card("*s"), Card("*")},
  };
  cout << "Suited connector hits straight/flush draw on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;

  // Test
  // Suited connector hits a straight/flush/two pair/trips on flop.
  myHand = {Card("7s"), Card("8s")};
  patterns = {
      {Card("4*"), Card("5*"), Card("6*")},  // straight
      {Card("5*"), Card("6*"), Card("9*")},  // straight
      {Card("6*"), Card("9*"), Card("T*")},  // straight
      {Card("9*"), Card("T*"), Card("J*")},  // straight
      {Card("*s"), Card("*s"), Card("*s")},  // flush
      {Card("7*"), Card("8*"), Card("*")},  // two pair
      {Card("7*"), Card("7*"), Card("*")},  // trips
      {Card("8*"), Card("8*"), Card("*")},  // trips
  };
  cout << "Suited connector hits straight/flush/two pair/trips or better on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;

  // Test
  // Suited connector hits a straight or flush on river.
  myHand = {Card("7s"), Card("8s")};
  patterns = {
      {Card("4*"), Card("5*"), Card("6*"), Card("*"), Card("*")},  // straight
      {Card("5*"), Card("6*"), Card("9*"), Card("*"), Card("*")},  // straight
      {Card("6*"), Card("9*"), Card("T*"), Card("*"), Card("*")},  // straight
      {Card("9*"), Card("T*"), Card("J*"), Card("*"), Card("*")},  // straight
      {Card("*s"), Card("*s"), Card("*s"), Card("*ns"), Card("*ns")},  // flush
  };
  cout << "Suited connector hits straight/flush on river: "
       << 100 * getProb(patterns, myHand) << '%' << endl;

  // Test
  // Suited connector hits two pair or trips on flop.
  myHand = {Card("7s"), Card("8s")};
  patterns = {
      {Card("7*"), Card("8*"), Card("*")},  // two pair
      {Card("7*"), Card("7*"), Card("*")},  // trips
      {Card("8*"), Card("8*"), Card("*")},  // trips
  };
  cout << "Suited connector hits two pair or trips on flop: "
       << 100 * getProb(patterns, myHand) << '%' << endl;

  // Test
  // Suited connector hits two pair or trips on river.
  myHand = {Card("7s"), Card("8s")};
  patterns = {
      {Card("7*"), Card("8*"), Card("*"), Card("*"), Card("*")},  // two pair
      {Card("7*"), Card("7*"), Card("*"), Card("*"), Card("*")},  // trips
      {Card("8*"), Card("8*"), Card("*"), Card("*"), Card("*")},  // trips
  };
  cout << "Suited connector hits two pair or trips on river: "
       << 100 * getProb(patterns, myHand) << '%' << endl;

  // Test
  // Pocket hits a set on flop.
  myHand = {Card("7s"), Card("7d")};
  patterns = {
      {Card("7*"), Card("*"), Card("*")},
  };
  cout << "Pocket hits a set on flop: " << 100 * getProb(patterns, myHand)
       << '%' << endl;

  // Test
  // Pocket hits a set on river.
  myHand = {Card("7s"), Card("7d")};
  patterns = {
      {Card("7*"), Card("*"), Card("*"), Card("*"), Card("*")},
  };
  cout << "Pocket hits a set on river: " << 100 * getProb(patterns, myHand)
       << '%' << endl;

  // Test
  // probability to get a playable hand.
  cout << "Probability to get a playable hand: "
       << 100 * getHandProb(reasonableHandRange) << '%' << endl;

  // Test
  // probability to get AA.
  patterns = {{Card("A*"), Card("A*")}};
  cout << "Probability to get AA: " << 100 * getHandProb(patterns) << '%'
       << endl;

  // Test
  // Probability that other player goes all in with AA, when I have KK.
  patterns = {{Card("A*"), Card("A*")}};
  myHand = {Card("Ks"), Card("Kh")};
  cout << "Probability that other player goes all in with AA, when I have KK: "
       << 100 * getHandProb(patterns, allInHandRange, myHand) << '%' << endl;

  // Test
  // Probability that other player goes all in with AA, when I have AK.
  othersHand = {{Card("A*"), Card("A*")}};
  myHand = {Card("As"), Card("Kh")};
  cout << "Probability that other player goes all in with AA, when I have AK: "
       << 100 * getHandProb(othersHand, allInHandRange, myHand) << '%' << endl;

  // Test
  // Probability that other player hits trips on flop.
  othersHand = {{Card("7*"), Card("*")}};
  board = {
      {Card("7s"), Card("7d"), Card("2s"),  // flop
       Card("As"), Card("Kh")}              // my hand
  };
  cout << "Probability that other player hits trips on flop: "
       << 100 * getHandProb(othersHand, reasonableHandRange, board) << '%'
       << endl;

  return 0;
}
