#include <iostream>

#ifndef BLACKJACK_H
#define BLACKJACK_H

class Blackjack {

  public:

    int bet(int funds,int min);
    int pullCard();
    int dealerInitial();
    int playerHand(int bet, int funds);
    int dealerFinal();




};



#endif
