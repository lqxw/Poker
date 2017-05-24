#ifndef TEXAS_H_
#define TEXAS_H_

#include <string>
#include <vector>

using namespace std;

class Card {
 public:
  Card(int num);

  // Support format: "*", "5*", "*c", "5c", "5nc"
  Card(string s);

  Card(int n, string s);

  bool operator==(const Card& other) const;

  void print() const;

 private:
  int value;    // 0 means match anything, -3 means not 3
  string suit;  // lowercase hsdc, * means match anything, "ns" means not spade

  bool checkNum(int a, int b) const;
  bool checkSuit(string a, string b) const;
};

// existingCards must be explicit defined, no regexp.
// Patterns much be ordered by decreasing strictness, and has same length.
float getHandProb(const vector<Card>& handPatterns,
                  const vector<Card>& existingCards = vector<Card>());

float getHandProb(const vector<vector<Card>>& handPatterns,
                  const vector<Card>& existingCards = vector<Card>());

float getHandProb(const vector<vector<Card>>& specificHandPatterns,
                  const vector<vector<Card>>& handRanges,  // size = 2
                  const vector<Card>& existingCards = vector<Card>());

float getProb(const vector<Card>& boardPatterns,
              const vector<Card>& existingCards);

float getProb(const vector<vector<Card>>& boardPatterns,
              const vector<Card>& existingCards);

#endif
