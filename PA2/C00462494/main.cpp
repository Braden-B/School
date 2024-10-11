#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include "Blackjack.h"
#include "Strategy.h"
using namespace std;

int main() {
    Blackjack blackjack;
    Strategy strategy;
    int previousScore = 0;
    bool hadAce = false;
    for (int f = 0; f < 100; f++) {
        cout<<"Loop "<<f<<endl;
        for (int u = 1; u <= 10000; u++) {
            blackjack.startRound();
            int choice = strategy.decide(blackjack.dealerHand[0], blackjack.getMaxHandValue(blackjack.playerHand),
                                     blackjack.hasUsableAce(blackjack.playerHand));
            while (choice != 0) {
                previousScore = blackjack.getMaxHandValue(blackjack.playerHand);
                hadAce = blackjack.hasUsableAce(blackjack.playerHand);
                blackjack.dealerHand.push_back(blackjack.drawCard());
                strategy.updateQVals(blackjack.dealerHand[0], previousScore, choice, 0,
                                     blackjack.getMaxHandValue(blackjack.playerHand), hadAce,
                                     blackjack.hasUsableAce(blackjack.playerHand));
                choice = strategy.decide(blackjack.dealerHand[0], blackjack.getMaxHandValue(blackjack.playerHand),
                                         blackjack.hasUsableAce(blackjack.playerHand));
                if (blackjack.getMaxHandValue(blackjack.playerHand) > 21) {
                    break;
                }
            }
            while (blackjack.getMaxHandValue(blackjack.dealerHand) < 17) {
                blackjack.dealerHand.push_back(blackjack.drawCard());
            }
            int r = blackjack.endRound();
            strategy.updateQVals(blackjack.dealerHand[0],previousScore, choice, r,
                                     blackjack.getMaxHandValue(blackjack.playerHand), hadAce,
                                     blackjack.hasUsableAce(blackjack.playerHand));
        }
        strategy.setEpsilon();
    }
}
