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
    for (int i = 0; i <= *cardsInHand-1; i++) {
        newHand[i] = handArray[i];
    }
    newHand[*cardsInHand] = valueOfCard;
    delete[] handArray;
    handArray = newHand;
    *cardsInHand = *cardsInHand + 1;
}

int countAcesInHand(int (*handArray), int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (handArray[i] == 0) {
            count++;
        }
    }
    return count;
}


int* evaluateHand(int (*handArray), int length) {
    int pointsTotal = 0;
    int acesInHand = countAcesInHand(handArray, length);
    int* handScoresPtr = new int [(int) pow(2, acesInHand)];
    int aces11 = acesInHand;
    int aces1 = 0;
    for (int i = 0; i<length; i++) {
        if (handArray[i] > 0)
            pointsTotal+= handArray[i];
    }
    handScoresPtr[0] = pointsTotal;
    if (acesInHand != 0) {
        for (int i = 0; i <= 2*acesInHand; i++) {
            pointsTotal = aces1 + aces11*11 + pointsTotal;
            if (pointsTotal > 21) {
                handScoresPtr[i+1] = -1;
            } else {
                handScoresPtr[i+1] = pointsTotal;
            }
            pointsTotal = pointsTotal - aces1 - aces11;
            aces1++;
            aces11--;
        }
    }
    return handScoresPtr;

}
string handToString(int (*hand), int length) {
    string result;
    int i = 0;
    while (i < length) {
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
    while (i < length) {
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
    while(quit == false) {
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
                if ((*evaluateHand(dealerHand, *player1LengthPtr) == 21)) {
                    for (int i = 0; i < countAcesInHand(playerHand1, player1Length); i++) {
                        if (*evaluateHand(playerHand1, *player1LengthPtr) == 21) {
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
            int player1Score = evaluateHand(playerHand1, *player1LengthPtr)[0];
            while (hitStayChoice != 2) {
                addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
                for (int i = 0; i <= countAcesInHand(playerHand1, *player1LengthPtr); i++) {
                    if (evaluateHand(playerHand1, *player1LengthPtr)[i] > player1Score) {
                        player1Score = evaluateHand(playerHand1, *player1LengthPtr)[i];
                    }
                }
                if (player1Score < 21) {
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
            hitStayChoice = 3;
            int dealerScore;
            while (hitStayChoice != 2) {
                dealerScore = 0;
                addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
                cout << "Dealer Turn. Their hand is " << handToString(dealerHand, dealerLength) << endl;
                for (int i = 0; i <= countAcesInHand(playerHand1, *player1LengthPtr); i++) {
                    if (evaluateHand(dealerHand, *dealerLengthPtr)[i] > dealerScore) {
                        dealerScore = evaluateHand(dealerHand, *dealerLengthPtr)[i];
                    }
                }

                if(dealerScore <= 16) {
                    hitStayChoice = 1;
                }


                hitStayChoice = 2;
                if (dealerScore == player1Score) {
                    cout<<"Push. Player 1 tied the dealer with score " << dealerScore<<endl;
                }
                else if(dealerScore > player1Score && dealerScore < 22) {
                    cout<<"Dealer beats player 1 with score " << dealerScore<<endl;
                    dealerWins++;
                }
                else if (dealerScore < player1Score && player1Score < 22) {
                    cout<<"Player 1 beats the dealer with score " << player1Score<<endl;
                    player1Wins++;
                }

                rounds++;
                cout << "Play another rounds? (1) Yes (2) No." << endl;
                int playChoice;
                cin >> playChoice;
                delete[] playerHand1;
                delete[] dealerHand;
                playerChoice = 0;
                if (playChoice == 2) {
                    cout << "Average Scores were " << dealerScore/rounds << " for the dealer, " << player1Score/rounds<<" for player 1, and " << endl;
                    quit = true;
                }
            }
        }
        if( playerChoice == 2)
            {
                int *dealerHand = new int [2];
                int *playerHand1 = new int [2];
                int *playerHand2 = new int [2];
                cout << "2 Players selected. Dealing." << endl;
                int *dealerLengthPtr = nullptr ;
                int dealerLength = 0;
                dealerLengthPtr = &dealerLength;
                addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
                addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
                int player1Length = 0;
                int * player1LengthPtr = &player1Length;
                addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
                addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
                int player2Length = 0;
                int * player2LengthPtr = &player2Length;
                addCardToHand(playerHand2, drawCard(liveDeckPointer, discardDeckPointer), player2LengthPtr);
                addCardToHand(playerHand2, drawCard(liveDeckPointer, discardDeckPointer), player2LengthPtr);
                for (int i = 0; i < countAcesInHand(dealerHand, dealerLength); i++) {
                    if ((*evaluateHand(dealerHand, *player1LengthPtr) == 21)) {
                        for (int i = 0; i < countAcesInHand(playerHand1, player1Length); i++) {
                            if (*evaluateHand(playerHand1, *player1LengthPtr) == 21) {
                                cout << "Push! Player 1 tied the dealer with a starting blackjack" << endl;
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
                cout << "Player 1 Turn." << endl;
                cout << "The dealer's hand is [?] " + handToStringDealer(dealerHand, dealerLength)<< endl;
                cout << "Your hand is " << handToString(playerHand1, player1Length) << endl;
                cout << "Would you like to hit (1) or stay (2)?" << endl;
                cin >> hitStayChoice;
                int player1Score = evaluateHand(playerHand1, *player1LengthPtr)[0];
                while (hitStayChoice != 2) {
                    addCardToHand(playerHand1, drawCard(liveDeckPointer, discardDeckPointer), player1LengthPtr);
                    for (int i = 0; i <= countAcesInHand(playerHand1, *player1LengthPtr); i++) {
                        if (evaluateHand(playerHand1, *player1LengthPtr)[i] > player1Score) {
                            player1Score = evaluateHand(playerHand1, *player1LengthPtr)[i];
                        }
                    }
                    if (player1Score < 21) {
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
                hitStayChoice = '3';
                cout << "Player 2 Turn." << endl;
                cout << "The dealer's hand is [?] " + handToStringDealer(dealerHand, dealerLength)<< endl;
                cout << "Your hand is " << handToString(playerHand2, player2Length) << endl;
                cout << "Would you like to hit (1) or stay (2)?" << endl;
                cin >> hitStayChoice;
                int player2Score = evaluateHand(playerHand2, *player2LengthPtr)[0];
                while (hitStayChoice != 2) {
                    addCardToHand(playerHand2, drawCard(liveDeckPointer, discardDeckPointer), player2LengthPtr);
                    for (int i = 0; i <= countAcesInHand(playerHand2, *player2LengthPtr); i++) {
                        if (evaluateHand(playerHand2, *player2LengthPtr)[i] > player2Score) {
                            player2Score = evaluateHand(playerHand2, *player2LengthPtr)[i];
                        }
                    }
                    if (player2Score < 21) {
                        cout << "Your hand is " << handToString(playerHand2, player2Length) << endl;
                        cout << "Would you like to hit (1) or stay (2)?" << endl;
                        cin >> hitStayChoice;
                    }
                    else if (player2Score > 21){
                        cout << "You busted." << endl;
                        cout << "Your hand was " << handToString(playerHand2, player2Length) << endl;
                        hitStayChoice = 2;
                    }
                    else {
                        cout << "You have blackjack!" << endl;
                        hitStayChoice = 2;
                    }
                }
                cout << "Dealer Turn. Their hand is " << handToString(dealerHand, dealerLength) << endl;
                hitStayChoice = 3;
                int dealerScore;
                while (hitStayChoice != 2) {
                    dealerScore = 0;
                    addCardToHand(dealerHand, drawCard(liveDeckPointer, discardDeckPointer), dealerLengthPtr);
                    cout << "Dealer Turn. Their hand is " << handToString(dealerHand, dealerLength) << endl;
                    for (int i = 0; i <= countAcesInHand(playerHand1, *player1LengthPtr); i++) {
                        if (evaluateHand(dealerHand, *dealerLengthPtr)[i] > dealerScore) {
                            dealerScore = evaluateHand(dealerHand, *dealerLengthPtr)[i];
                        }
                    }

                    if(dealerScore <= 16) {
                        hitStayChoice = 1;
                    }


                    hitStayChoice = 2;
                    if (dealerScore == player1Score) {
                        cout<<"Push. Player 1 tied the dealer with score " << dealerScore<<endl;
                    }
                    else if(dealerScore > player1Score && dealerScore < 22) {
                        cout<<"Dealer beats player 1 with score " << dealerScore<<endl;
                        dealerWins++;
                    }
                    else if (dealerScore < player1Score && player1Score < 22) {
                        cout<<"Player 1 beats the dealer with score " << player1Score<<endl;
                        player1Wins++;
                    }
                    if (dealerScore == player2Score) {
                        cout<<"Push. Player 2 tied the dealer with score " << dealerScore<<endl;
                    }
                    else if(dealerScore > player2Score && dealerScore < 22) {
                        cout<<"Dealer beats player 2 with score " << dealerScore<<endl;
                        dealerWins++;
                    }
                    else if (dealerScore < player2Score && player2Score < 22) {
                        cout<<"Player 2 beats the dealer with score " << player2Score<<endl;
                        player2Wins++;
                    }
                    else if (dealerScore > 21 && player2Score > 21 && player1Score > 21) {
                        cout<<"No winners, everyone busted"<<endl;
                    }

                    rounds++;
                    cout << "Play another rounds? (1) Yes (2) No." << endl;
                    int playChoice;
                    cin >> playChoice;
                    playerChoice = 0;
                    delete[] playerHand1;
                    delete[] playerHand2;
                    delete[] dealerHand;
                    if (playChoice == 2) {
                        cout << "Average Scores were " << dealerScore/rounds << " for the dealer, " << player1Score/rounds<<" for player 1, and " << player2Score/rounds <<" for player 2." <<endl;
                        quit = true;
                    }
                }
            }
        }
    }





