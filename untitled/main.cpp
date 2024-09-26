#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void shuffleDecks(int (*liveDeck), int (*discardDeck)) {
    for (int i = 0; i < 10; i++) {
        liveDeck[i] = liveDeck[i] + discardDeck[i];
    }
}

int countCardsInDeck(int (*liveDeck)) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        count = liveDeck[i] + count;
    }
    return count;
}

int drawCard(int (*liveDeck), int (*discardDeck)) {
    if (countCardsInDeck(liveDeck) < 21) {
        shuffleDecks(liveDeck, discardDeck);
    }
    int x = 20;

    while (x > 9) {
        x = rand()%9;
    }
    liveDeck[x]--;
    discardDeck[x]++;
    return x;
}

void addCardToHand(int *&handArray, int valueOfCard, int *&cardsInHand) {
    int *newHand = new int [*cardsInHand];
    int cards = *cardsInHand++;
    for (int i = 0; i <= *cardsInHand-1; i++) {
        newHand[i] = handArray[i];
    }
    newHand[*cardsInHand] = valueOfCard;
    delete[] handArray;
    handArray = newHand;
    delete[] cardsInHand;
    cardsInHand = &cards;
}

int countAcesInHand(int (*handArray), int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (handArray[i] == 1) {
            count++;
        }
    }
    return count;
}


auto evaluateHand(int (*handArray), const int acesInHand) {
    int size;
    if (acesInHand == 0) {
        size = 1;
    } else {
        size = acesInHand;
    }
    int pointsTotal = 0;
    int handScores[(int) pow(2, acesInHand)];
    int* handScoresPtr = handScores;
    int i = 1;
    while (handArray[i] != 0) {
        pointsTotal += i;
        i++;
    }
    handScoresPtr[0] = pointsTotal;
    int aces11 = acesInHand;
    int aces1 = 0;
    if (acesInHand != 0) {
        for (i = 0; i <= acesInHand; i++) {
            pointsTotal = aces1 + aces11*11 + pointsTotal;
            if (pointsTotal > 21) {
                handScoresPtr[i] = -1;
            } else {
                handScoresPtr[i] = pointsTotal;
            }
            pointsTotal = pointsTotal - aces1 - aces11;
            aces1++;
            aces11--;
        }
        return handScoresPtr;
    } else {
        return handScoresPtr;
    }

}

string handToString(int (*hand), int length) {
    string result;
    int i = 0;
    while (i <= length) {
        if (hand[i] == 0) {
            result += "[A] ";
            i++;
        } else {
            result += "[" + to_string(hand[i]) + "] ";
            i++;
        }
    }
    return result;
}

string handToStringDealer(int *hand, int length) {
    string result;
    int i = 1;
    int value = 0;
    while (i <= length) {
        value = (hand[i]);
        if (value == 0) {
            result += "[A] ";
            i++;
        } else {
            result += "[" + to_string(value) + "] ";
            i++;
        }
    }
    return result;
}

int main() {
    int LiveDeck[10] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 64};
    int DiscardDeck[10];
    int *liveDeckPointer = LiveDeck;
    int *discardDeckPointer = DiscardDeck;
    int rounds = 0;
    int player1Wins = 0;
    int player2Wins = 0;
    int dealerWins = 0;
    bool quit = false;
    shuffleDecks(liveDeckPointer, discardDeckPointer);
    cout << "Hello. Would you like to play with 1 or 2 players?" << endl;
    int playerChoice;
    while (playerChoice != 1 and playerChoice != 2) {
        cin >> playerChoice;
    }
    if (playerChoice == 1) {
        int *dealerHand = new int [2];
        int *playerHand1 = new int [2];
        cout << "1 Player selected. Dealing." << endl;
        int *dealerLengthPtr = nullptr ;
        int dealerLength = 0;
        dealerLengthPtr = &dealerLength;
        addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
        addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
        int player1Length = 0;
        int * player1LengthPtr = &player1Length;
        addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
        addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
        for (int i = 0; i < countAcesInHand(dealerHand, dealerLength); i++) {
            if ( int(evaluateHand(dealerHand, countAcesInHand(dealerHand, dealerLength))[i]) == 21) {
                for (int i = 0; i < countAcesInHand(playerHand1, player1Length); i++) {
                    if (evaluateHand(playerHand1, countAcesInHand(playerHand1, player1Length))[i] == 21) {
                        cout << "Push! You tied the dealer with a starting blackjack" << endl;
                    }
                    else {
                        cout << "The dealer wins with a starting blackjack." << endl;
                    }
                    break;
                }
            }
            break;
        }
        int hitStayChoice = '3';
        cout << "The dealer's hand is [?] " + handToStringDealer(dealerHand, dealerLength)<< endl;
        cout << "Your hand is " << handToString(playerHand1, player1Length) << endl;
        cout << "Would you like to hit (1) or stay (2)?" << endl;
        cin >> hitStayChoice;
        int player1Score = evaluateHand(playerHand1, countAcesInHand(playerHand1, player1Length))[0];
        while (hitStayChoice != 2) {
            for (int i = 0; i < countAcesInHand(playerHand1, player1Length); i++) {
                if (evaluateHand(playerHand1, countAcesInHand(playerHand1, player1Length))[i] > player1Score) {
                    player1Score = evaluateHand(playerHand1, countAcesInHand(playerHand1, player1Length))[i];
                }
            }
            if (player1Score < 21) {
                player1Length++;
                player1LengthPtr = &player1Length;
                addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
                cout << "Your hand is " << handToString(playerHand1, player1Length) << endl;
                cout << "Would you like to hit (1) or stay (2)?" << endl;
                cin >> hitStayChoice;
            }
            else if (player1Score > 21){
                cout << "You busted." << endl;
                cout << "Your hand was " << handToString(playerHand1, player1Length) << endl;
                hitStayChoice = 2;
            }
            else {
                cout << "You have blackjack!" << endl;
                hitStayChoice = 2;
            }
        }
        cout << "Dealer Turn. Their hand is " << handToString(dealerHand, dealerLength) << endl;
        hitStayChoice = '3';
        while (hitStayChoice != '2') {
            dealerLength++;
            dealerLengthPtr = &dealerLength;
            addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
            int dealerScore = 0;
            while (hitStayChoice != 2) {
                for (int i = 0; i < player1Length; i++) {
                    if (evaluateHand(dealerHand, countAcesInHand(dealerHand, dealerLength))[i] > player1Score) {
                        dealerScore = evaluateHand(dealerHand, countAcesInHand(dealerHand, dealerLength))[i];
                    }
                }
                if (dealerScore < 16) {
                    dealerLength++;
                    dealerLengthPtr = &dealerLength;
                    addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
                    cout << "Dealer hand is " << handToString(dealerHand, dealerLength) << endl;
                    if (evaluateHand(dealerHand, countAcesInHand(dealerHand, dealerLength) < 16)) {
                        hitStayChoice = 1;
                    }
                    else if (dealerScore > 21){
                        cout << "Dealer busted." << endl;
                        hitStayChoice = '2';
                    }
                    else {
                        cout << "Dealer has blackjack!" << endl;
                        hitStayChoice = '2';
                    }
                }
            }
            if (dealerScore == player1Score) {
                cout<<"Push. Tie game with score " << dealerScore<<endl;
            }
            else if(dealerScore > player1Score && dealerScore < 22) {
                cout<<"Dealer wins with score " << dealerScore<<endl;
                dealerWins++;
            }
            else if (dealerScore < player1Score && player1Score < 22) {
                cout<<"Player 1 wins with score " << player1Score<<endl;
                player1Wins++;
            }
            else if (dealerScore > 21 && player1Score > 21) {
                cout<<"No winners, you both busted"<<endl;
            }
            rounds++;
            int playChoice;
            cout << "Play another rounds? (1) Yes (2) No." << endl;
            cin >> playChoice;
            if (playChoice == 2) {
                cout << "Average Scores were " << dealerScore/rounds << " for the dealer and " << player1Score/rounds<<" for player 1." <<endl;
                quit = true;
            }
        }
    }
}
