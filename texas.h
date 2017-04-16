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

const int RUNTIMES = 100000;
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
