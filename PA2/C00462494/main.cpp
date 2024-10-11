#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include "Blackjack.cpp"
#include "Strategy.cpp"
using namespace std;

int main() {
    Blackjack blackjack;
    Strategy strategy;
    int choice;
    bool bust = false;
    bool playerBust = false;
    vector<int> * playerHandPointer = &blackjack.playerHand;
    vector<int> * dealerHandPointer = &blackjack.dealerHand;
    int previousScore = 0;
    bool hadAce = false;
    int r = 0;
    for (int j = 0; j < 100; j++) {
        for (int i = 1; i <= 100000; i++) {
            blackjack.startRound();
            choice = strategy.decide(blackjack.getHandDealer()[1], blackjack.getMaxHandValue(*playerHandPointer),
                                     blackjack.hasUsableAce(*playerHandPointer));
            while (choice != 0) {
                previousScore = blackjack.getMaxHandValue(*playerHandPointer);
                hadAce = blackjack.hasUsableAce(*playerHandPointer);
                blackjack.getHandDealer().push_back(blackjack.drawCard());
                strategy.updateQVals(blackjack.getHandDealer()[1], previousScore, choice, 0,
                                     blackjack.getMaxHandValue(*playerHandPointer), hadAce,
                                     blackjack.hasUsableAce(*playerHandPointer));
                choice = strategy.decide(blackjack.getHandDealer()[1], blackjack.getMaxHandValue(*playerHandPointer),
                                         blackjack.hasUsableAce(*playerHandPointer));
                if (blackjack.getMaxHandValue(*playerHandPointer) > 21) {
                    bust = true;
                    break;
                }
            }
            while (blackjack.getMaxHandValue(*dealerHandPointer) < 17) {
                blackjack.getHandDealer().push_back(blackjack.drawCard());
            }
            r = blackjack.endRound();
            strategy.updateQVals(blackjack.getHandDealer()[1], previousScore, choice, 0,
                                     blackjack.getMaxHandValue(*playerHandPointer), hadAce,
                                     blackjack.hasUsableAce(*playerHandPointer));
        }
        strategy.setEpsilon();
    }
}
