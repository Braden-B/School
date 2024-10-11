#include "Strategy.h"

// constructor for the strategy object meant to handle q values and epsilon. It initialises epsilon and the q value tables, setting every value to 0.1 to start
Strategy::Strategy() {
    this->epsilon = 1.0;
    vector x(11, vector<vector<double> >(30, vector<double>(2, 0.1)));
    vector y(11, vector<vector<double> >(30, vector<double>(2, 0.1)));
    this->QValsNoAce = x;
    this->QValsWithAce = y;
}

//This method takes a given hand value, the dealer shown card, and whether the player has a usable ace to return a q value from the table which then determines the action to be taken
// if the generated random is less than epsilon, it flips the resulting action to explore
int Strategy::decide(int dealerShow, int playerHas, bool usableAce) {
    if ((double) rand() / (double) RAND_MAX < (1 - epsilon)) {
        if (usableAce) {
            if (this->QValsWithAce[dealerShow][playerHas][0] >= this->QValsWithAce[dealerShow][playerHas][1]) {
                return 1;
            } else return 0;
        } else {
            if (this->QValsNoAce[dealerShow][playerHas][0] >= this->QValsNoAce[dealerShow][playerHas][1]) {
                return 1;
            } else return 0;
        }
    } else {
        if (this->QValsNoAce[dealerShow][playerHas][0] >= this->QValsNoAce[dealerShow][playerHas][1]) {
            return 0;
        } else return 1;
    }
}


//This function updates the q value for any chosen action. For non-terminal cases is updates the value with the best possible reward, but for terminal cases it updates either
// a win and an increase in q value, or a loss with a decrease in q value.
void Strategy::updateQVals(int dealerShow, int playerHad, int action, double r, int playerHas, bool hadUsableAce,
                           bool hasUsableAce) {
    double qValue;
    double alpha = 0.00005;
    double gamma = 0.99;
    double estimatedQVal;
    if (r == 0) {
        if (hasUsableAce) {
            qValue = QValsWithAce[dealerShow][playerHas][action];
            if (qValue > QValsWithAce[dealerShow][playerHas][(action / 1)]) {
                estimatedQVal =
                        qValue + (alpha * (r + (gamma * (QValsWithAce[dealerShow][(playerHas + (21 - playerHas) % 10)][
                                                    action])) - qValue));
            } else {
                qValue = QValsWithAce[dealerShow][playerHas][(action / 1)];
                estimatedQVal =
                        qValue + (alpha * (r + (gamma * (QValsWithAce[dealerShow][(playerHas + (21 - playerHas) % 10)][
                                                    action])) - qValue));
            }
        } else {
            qValue = QValsNoAce[dealerShow][playerHas][action];
            if (qValue > QValsNoAce[dealerShow][playerHas][(action / 1)]) {
                estimatedQVal =
                        qValue + (alpha * (r + (gamma * (QValsNoAce[dealerShow][(playerHas + (21 - playerHas) % 10)][
                                                    action])) - qValue));
            } else {
                qValue = QValsNoAce[dealerShow][playerHas][(action / 1)];
                estimatedQVal =
                        qValue + (alpha * (r + (gamma * (QValsNoAce[dealerShow][(playerHas + (21 - playerHas) % 10)][
                                                    action])) - qValue));
            }
        }
        if (hasUsableAce) {
            QValsWithAce[dealerShow][playerHas][action] = estimatedQVal;
        } else {
            QValsNoAce[dealerShow][playerHas][action] = estimatedQVal;
        }
    }
    if (r == 1) {
        if (hasUsableAce) {
            qValue = QValsWithAce[dealerShow][playerHas][action];
            QValsWithAce[dealerShow][playerHas][action] = qValue + alpha * (r - qValue);
        } else {
            qValue = QValsNoAce[dealerShow][playerHas][action];
            QValsNoAce[dealerShow][playerHas][action] = qValue + alpha * (r - qValue);
        }
    }
    if (r == -1) {
        if (hadUsableAce) {
            qValue = QValsWithAce[dealerShow][playerHad][action];
            QValsWithAce[dealerShow][playerHad][action] = qValue + alpha * (r - qValue);
        } else {
            qValue = QValsNoAce[dealerShow][playerHad][action];
            QValsNoAce[dealerShow][playerHad][action] = qValue + alpha * (r - qValue);
        }
    }
}

//this method updates epsilon when called, decreasing epsilon by 0.01 or limiting it to 0.0001
void Strategy::setEpsilon() {
    this->epsilon = max(0.0001, epsilon-0.01);
}

