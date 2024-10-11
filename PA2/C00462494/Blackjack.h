#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

using namespace std;

class Blackjack {
public:
    vector<int> dealerHand;
    vector<int> playerHand;
    Blackjack();
    void startRound();
    int drawCard();
    bool hasUsableAce(vector<int> &inputHand);
    int getMinHandValue(vector<int> &inputHand);
    int getMaxHandValue(vector<int> &inputHand);
    int endRound();
};



#endif //BLACKJACK_H
