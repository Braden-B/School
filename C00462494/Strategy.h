#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include<cmath>

using namespace std;

class Strategy {
public:
    double epsilon;
    vector<vector<vector<double>>> QValsNoAce, QValsWithAce;
    Strategy();
    int decide(int dealerShow, int playerHas, bool usableAce);
    void updateQVals(int dealerShow, int playerHad, int action, double r, int playerHas, bool hadUsableAce, bool hasUsableAce);
};



#endif //STRATEGY_H
