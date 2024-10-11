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

vector<int> Blackjack::getHandPlayer() {
    return this->playerHand;
}

vector<int> Blackjack::getHandDealer() {
    return this->dealerHand;
}

void Blackjack::startRound() {
    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
}

// gets hand value assuming all aces are 1. returns an integer
int getMinHandValue(vector<int> &hand) {
    int value = 0;
    for (int i = 0; i < hand.size(); i++) {
        value += hand[i];
    }
    return value;
}

// checks the hand to see if it has an ace that can be values at 11 and not 1, returns a boolean
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

// returns the highest value a hand can be played at, meaning checking for usable aces and returning an integer
int getMaxHandValue(vector<int> &hand) {
    int maxValue = getMinHandValue(hand);
    if (hasUsableAce(hand)) {
        maxValue = maxValue + 10;
    }
    return maxValue;
}

int Blackjack::endRound() {
    int dealerScore = getMaxHandValue(dealerHand);
    if (dealerScore > 21) {
        return 1;
    }
    int playerScore = getMaxHandValue(playerHand);
    if (playerScore > 21) {
        return -1;
    }
    dealerHand.clear();
    playerHand.clear();
    if (dealerScore > playerScore) {
        return -1;
    }
    if (dealerScore < playerScore) {
        return 1;
    }
    return 0;
}
