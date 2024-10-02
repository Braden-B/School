#include "Blackjack.h"
#include <cmath>
#include <string>
using namespace std;

int drawCard() {
    int card = (rand() % 10) + 1;
    while (card > 10) {
        card = (rand() % 10) + 1;
    }
    return card;
};
void startRound() {
Blackjack blackjack;
    blackjack.dealerHand.push_back(drawCard());
    blackjack.dealerHand.push_back(drawCard());
    blackjack.playerHand.push_back(drawCard());
    blackjack.playerHand.push_back(drawCard());
}
int getMinHandValue(vector<int> &hand) {
    int value = 0;
    for (int i = 0; i < hand.size(); i++) {
        value += hand[i];
    }
    return value;
}
bool hasUsableAce(vector<int> &hand) {
    bool hasAce = false;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i] == 1) {
            hasAce = true;
            break;
        }
    }
    if (getMinHandValue(hand) + 10 <= 21)
        return true;
    return false;
}

int getMaxHandValue(vector<int> &hand) {
    int maxValue = getMinHandValue(hand);
    if (hasUsableAce(hand)) {
        maxValue = maxValue+10;
    }
    return maxValue;
}
int endRound() {
    int playChoice = 1;
    while (playChoice == 1) {
        blackjack.playerHand.push_back(drawCard());

    }
    while (getMaxHandValue(blackjack.dealerHand)<17) {
        blackjack.dealerHand.push_back(drawCard());
    }
    int dealerScore = getMaxHandValue(blackjack.dealerHand);
    if (dealerScore > 21) {
        return 1;
    }
    int playerScore = getMaxHandValue(blackjack.playerHand);
    if (playerScore > 21) {
        return -1;
    }
    blackjack.dealerHand.clear();
    blackjack.playerHand.clear();
    if (dealerScore > playerScore) {
        return -1;
    }
    if (dealerScore < playerScore) {
        return 1;
    }
    return 0;
}