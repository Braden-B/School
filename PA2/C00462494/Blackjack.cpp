#include "Blackjack.h"
#include <cmath>
#include <string>
using namespace std;

Blackjack::Blackjack() {
    vector<int> dealerHand = vector<int>();
    vector<int> playerHand = vector<int>();
}

int Blackjack::drawCard() {
    int card = (rand() % 10) + 1;
    while (card > 10) {
        card = (rand() % 10) + 1;
    }
    return card;
};

void Blackjack::startRound() {
    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
}

// gets hand value assuming all aces are 1. returns an integer
int Blackjack::getMinHandValue(vector<int> &hand) {
    int value = 0;
    for (int i : hand) {
        value += i;
    }
    if (value > 21) {
        return 22;
    }
    return value;
}

// checks the hand to see if it has an ace that can be values at 11 and not 1, returns a boolean
bool Blackjack::hasUsableAce(vector<int> &hand) {
    bool hasAce = false;
    for (int i : hand) {
        if (i == 1) {
            hasAce = true;
            break;
        }
    }
    if (getMinHandValue(hand) + 10 <= 21)
        return hasAce;
    return hasAce;
}

// returns the highest value a hand can be played at, meaning checking for usable aces and returning an integer
int Blackjack::getMaxHandValue(vector<int> &hand) {
    int maxValue = getMinHandValue(hand);
    if (hasUsableAce(hand)) {
        maxValue = maxValue + 10;
    }
    return maxValue;
}

int Blackjack::endRound() {
    int dealerScore = getMaxHandValue(dealerHand);
    int playerScore = getMaxHandValue(playerHand);

    dealerHand.clear();
    playerHand.clear();
    if (dealerScore > playerScore && dealerScore <= 21) {
        return -1;
    }
    if (dealerScore < playerScore && playerScore <= 21) {
        return 1;
    }
    return 0;
}
