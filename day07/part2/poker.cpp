#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum HandTypes {
  FIVE_OF_A_KIND,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  THREE_OF_A_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD
};

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

class Card {
private:
  char card;
  int value;
public:

  Card (char c) {
    card = c;
    if (isNumber(c)) {
      value = c - '0';
    } else if (c == 'T') {
      value = 10;
    } else if (c == 'J') {
      value = 0;
    } else if (c == 'Q') {
      value = 12;
    } else if (c == 'K') {
      value = 13;
    } else if (c == 'A') {
      value = 14;
    }
  }

  ~Card(){}

  char getCard() {
    return card;
  }

  int getValue() {
    return value;
  }

  bool operator== (const Card& other) {
    return value == other.value;
  }

  bool operator> (const Card &other) {
    return value > other.value;
  }
};

class Hand {
private:
  int cardCounts[15] = { 0 };
  vector<Card> cards;
  int nJokers = 0;
  string cardsString;
  int bid;
  HandTypes handType;
public:
  Hand(string cs, int b) {
    cardsString = cs;
    bid = b;
    for (char c : cs) {
      Card *card = new Card(c);
      cards.push_back(*card);
      if (c == 'J') {
        nJokers += 1;
      } else {
        cardCounts[card->getValue()] += 1;
      }
    }
    if (this->isFiveOfAKind()) {
      handType = FIVE_OF_A_KIND;
    } else if (this->isFourOfAKind()) {
      handType = FOUR_OF_A_KIND;
    } else if (this->isFullHouse()) {
      handType = FULL_HOUSE;
    } else if (this->isThreeOfAKind()) {
      handType = THREE_OF_A_KIND;
    } else if (this->isTwoPair()) {
      handType = TWO_PAIR;
    } else if (this->isPair()) {
      handType = ONE_PAIR;
    } else {
      handType = HIGH_CARD;
    }
  }

  ~Hand() {}

  string getCards() {
    return cardsString;
  }

  int getBid() {
    return bid;
  }

  bool isFiveOfAKind() {
    for (int count : cardCounts) {
      if ((count + nJokers) == 5) {
        return true;
      }
    }
    return false;
  }

  bool isFourOfAKind() {
    for (int count : cardCounts) {
      if ((count + nJokers) == 4) {
        return true;
      }
    }
    return false;
  }
  
  bool isFullHouse() {
    bool twoCountFound = false;
    bool threeCountFound = false;
    for (int count : cardCounts) {
      if (!threeCountFound && (count + nJokers) == 3) {
        threeCountFound = true;
        continue;
      }
      if (count == 2) {
        twoCountFound = true;
      }
    }
    return twoCountFound && threeCountFound;
  }

  bool isThreeOfAKind() {
    bool twoCountFound = false;
    bool threeCountFound = false;
    for (int count : cardCounts) {
      if (!threeCountFound && (count + nJokers) == 3) {
        threeCountFound = true;
        continue;
      }
      if (count == 2) {
        twoCountFound = true;
      }
    }
    return !twoCountFound && threeCountFound;
  }

  bool isTwoPair() {
    bool firstTwoCountFound = false;
    bool secondTwoCountFound = false;
    for (int count : cardCounts) {
      if (count == 2) {
        if (firstTwoCountFound) {
          secondTwoCountFound = true;
        } else {
          firstTwoCountFound = true;
        }
      }
    }
    return firstTwoCountFound && secondTwoCountFound;
  }

  bool isPair() {
    if (this->isFullHouse() || this->isTwoPair()) {
      return false;
    }

    for (int count : cardCounts) {
      if ((count + nJokers) == 2) {
        return true;
      }
    }
    return false;
  }
  
  bool isHighCard() {
    if (nJokers > 0) {
      return false;
    }
    for (int count : cardCounts) {
      if (count > 1) {
        return false;
      }
    }
    return true;
  }

  bool operator> (Hand &other) {
    if (this->handType == other.handType) {
      for (int i = 0; i < 5; i += 1) {
        if (this->cards[i] == other.cards[i]) {
          continue;
        }
        return this->cards[i] > other.cards[i];
      }
    }

    return this->handType < other.handType;
  }

  bool operator< (Hand &other) {
    return !(*this > other);
  }
};

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  vector<Hand> hands;
  for (string line : lines) {
    string cardString = line.substr(0, 5);
    int bid = stoi(line.substr(6));
    Hand *hand = new Hand(cardString, bid);
    hands.push_back(*hand);
  }
  sort(hands.begin(), hands.end(), [](Hand &a, Hand &b) { return b > a; });

  int winnings = 0;
  for (int i = 0; i < hands.size(); i += 1) {
    winnings += hands[i].getBid() * (i + 1);
  }
  cout << winnings << endl;
}
