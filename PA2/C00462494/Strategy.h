#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include<cmath>

using namespace std;

class Strategy {
public:
    double epsilon;
    vector<vector<vector<double>>> QValsNoAce, QValsWithAce;
    // I've written the program such that the first vector is dealer show card, second is player hand, and the third is hit or stay with 0 being stay and 1 being hit
    Strategy();
    int decide(int dealerShow, int playerHas, bool usableAce);
    void updateQVals(int dealerShow, int playerHad, int action, double r, int playerHas, bool hadUsableAce, bool hasUsableAce);
    void setEpsilon();
};



#endif //STRATEGY_H
