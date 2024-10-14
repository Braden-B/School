#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include "Blackjack.h"
#include "Strategy.h"
using namespace std;

int main() {
    std::mt19937 generator(0);
    Blackjack blackjack;
    Strategy strategy;
    int previousScore = 0;
    bool hadAce = false;
    double score = 0.0;
    for (int f = 0; f < 100; f++) {
        cout<<"Loop "<<f<<endl;
        for (int u = 1; u <= 100000; u++) {
            blackjack.startRound();
            int choice = strategy.decide(blackjack.dealerHand[0], blackjack.getMaxHandValue(blackjack.playerHand),
                                     blackjack.hasUsableAce(blackjack.playerHand));
            while (choice == 1) {
                previousScore = blackjack.getMaxHandValue(blackjack.playerHand);
                hadAce = blackjack.hasUsableAce(blackjack.playerHand);
                blackjack.playerHand.push_back(blackjack.drawCard());
                choice = strategy.decide(blackjack.dealerHand[0], blackjack.getMaxHandValue(blackjack.playerHand),
                                         blackjack.hasUsableAce(blackjack.playerHand));

                if (blackjack.getMaxHandValue(blackjack.playerHand) > 21) {
                    break;
                }
                int size = blackjack.playerHand.size();
                Blackjack hand;
                hand.playerHand = blackjack.playerHand;
                while (size > 2) {
                    int dealerShow = blackjack.dealerHand[0];
                    int hasScore = blackjack.getMaxHandValue(hand.playerHand);
                    bool hasAce = blackjack.hasUsableAce(hand.playerHand);
                    hand.playerHand.pop_back();
                    strategy.updateQVals(dealerShow,blackjack.getMaxHandValue(hand.playerHand), choice, 0,
                                         hasScore, blackjack.hasUsableAce(hand.playerHand),
                                         hasAce);
                    size--;
                }
                hand.playerHand.clear();
            }
            while (blackjack.getMaxHandValue(blackjack.dealerHand) < 17) {
                blackjack.dealerHand.push_back(blackjack.drawCard());
            }

            Blackjack hand;
            hand.playerHand = blackjack.playerHand;
            hand.dealerHand = blackjack.dealerHand;
            double r = blackjack.endRound();

            strategy.updateQVals(hand.dealerHand[0],previousScore, choice, r,
                                     blackjack.getMaxHandValue(hand.playerHand), hadAce,
                                     blackjack.hasUsableAce(hand.playerHand));
            score += r;
            hand.playerHand.clear();
            hand.dealerHand.clear();
        }
        cout<<"Score on Round "<<f<<": "<<(1.0*score)/100000.0<<endl;
        score = 0;
        strategy.setEpsilon();
    }
    cout<<"Without Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        cout<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            cout<<strategy.decide(f,u,0)<<" ";
        }
        cout<<endl;
    }
    cout<<"With Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        cout<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            cout<<strategy.decide(f,u,1)<<" ";
        }
        cout<<endl;
    }
    ofstream outputFile;
    outputFile.open("C00462494-Policy.txt");
    outputFile<<"Without Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        outputFile<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            outputFile<<strategy.QValsNoAce[f][u][0]<<" ";
        }
        outputFile<<endl;
    }
    outputFile<<"With Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        outputFile<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            outputFile<<strategy.QValsWithAce[f][u][1]<<" ";
        }
        outputFile<<endl;
    }
    outputFile<<"Without Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        outputFile<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            outputFile<<strategy.decide(f,u,0)<<" ";
        }
        outputFile<<endl;
    }
    outputFile<<"With Usable Ace"<<endl;
    for (int f = 1; f < 11; f++) {
        outputFile<<"Dealer Shows "<< f << ": ";
        for (int u = 14; u <= 21; u++) {
            outputFile<<strategy.decide(f,u,1)<<" ";
        }
        outputFile<<endl;
    }
    outputFile.close();
}

