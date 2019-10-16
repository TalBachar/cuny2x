#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include"Blackjack.hpp"

using namespace std;
  int Blackjack::bet(int funds,int min){
  int betAmount;
  cout << "Place your bets! Remember, the minimum in this table is " << min << "$." << endl;
  cout << "That means you can bet on " << min <<"$, " << min*2 << "$, " << min*3 << "$ and so on: ";
  cin >> betAmount;
  while (betAmount < min) {
    cout << "Your bet is lower than the minimum! Place a bet of at least " << min << "$ please: ";
    cin >> betAmount;
  }
  while (betAmount % min != 0) {
    cout << "Your bet must be a multiple of " << min << ". please place your bet. ";
    cin >> betAmount;
  }
  return betAmount;
  } //end bet()

  int Blackjack::pullCard() {
    int card = rand() % 13 + 1;
    if (card == 1) {cout << "Ace";}
    else if (card == 11) {cout << "Jack";
    card = 10;}
    else if (card == 12) {cout << "Queen";
    card = 10;}
    else if (card == 13) {cout << "King";
    card = 10;}
    else {cout << card;}

    return card;
  } //end pullCard()

  int Blackjack::playerHand(int bet, int funds) {

    cout << "\n\tPlayer has: ";
    //first card
    int playerCardsArr[21];
    playerCardsArr[1] = pullCard();
    cout << " and ";
    //second card
    playerCardsArr[2] = pullCard();

    if (playerCardsArr[1] == 1) { //blackjack first card Ace
      if (playerCardsArr[2] == 10) {
        cout << "\nBlackjack!!" <<endl;
        return 150;                    //if player has blackjack, return 150
      }
    } //end blackjack first card Ace
    if (playerCardsArr[1] == 10) { //blackjack second card Ace
      if (playerCardsArr[2] == 1) {
        cout << "\nBlackjack!!" <<endl;
        return 150;                    //if player has blackjack, return 150
      }
    } //end blackjack second card Ace

    cout << "\n\tDealer has: ";     //names the dealer's card
    dealerInitial();


    int sumCards = playerCardsArr[1] + playerCardsArr[2]; //initial sum of first 2cards
    cout << "\nSum of your cards is " << sumCards << endl;

    cout << "Would you like to: (H)hit / (S)stand / (D)double Down";
    if (playerCardsArr[1] == playerCardsArr[2]) {cout << " / (P)split";} //split option in case of pair
    cout << "\n";

    char action;
    cin >> action;

    //---------------------invalid input
    while (action != 'S' && action != 's' && action != 'H' && action != 'h' && action != 'D' && action != 'd'
    && action != 'P' && action != 'p') {
      cout << "Invalid action. Please choose: (H)hit / (S)stand / (D)double Down";
      if (playerCardsArr[1] == playerCardsArr[2]) {cout << " / (P)split";}
      cin >> action;
    }//end of invalid input

    //---------------------Double down--------------------
    if (action =='D' || action =='d') {
      if (funds < bet*2) { // if insufficient funds for DD
        cout << "You do not have enough chips to double-down. Choose another action:" << endl;
        cout << "(H)hit / (S)stand";
        if (playerCardsArr[1] == playerCardsArr[2]) {cout << " / (P)split";}
        cin >> action;
      } //end of insufficient funds for DD
      else if (funds >= bet*2) {
        bet = bet*2;
        cout << "Double Down! Card is: ";
        playerCardsArr[3] = pullCard();
        sumCards = playerCardsArr[1] + playerCardsArr[2] + playerCardsArr[3];
        cout << "\nSum of your hand is: " << sumCards << endl;
        return sumCards;
      }
    }//--------------------end of Double Down--------------------

    //---------------------Stand--------------------
    if (action == 'S' || action == 's') {
      cout << "Player stands on " << sumCards << endl;
      sumCards = playerCardsArr[1] + playerCardsArr[2];
      return sumCards;                      //player stands, return sum of cards
    }//--------------------end of Stand--------------------

    //---------------------Hit--------------------
    if (action == 'H' || action == 'h') {
      for (int i=3; i < sumCards; i++) {
        cout << "Hit! Card is: ";
        playerCardsArr[i] = pullCard();
        sumCards += playerCardsArr[i]; //update sum of cards with new card
        cout << "\nSum of your hand is: " << sumCards <<endl;
        if (sumCards > 21) {          //if >21 player busts
          cout << "Player busts!" << endl;
          return sumCards;
        }
        if (sumCards == 21) {         //if 21 player stands
          cout << "Player stands." << endl;
          return sumCards;
        }
        cout << "Press (S)stand, or any other key to hit again: ";
        cin >> action;
        if (action == 's' || action =='S') {
          return sumCards;
        }

      }
    }//--------------------end of Hit--------------------



  return 0;
  }//end of playerHand()

  int Blackjack::dealerInitial() {
    int dealerCard = pullCard(); //Dealer's first card

    return dealerCard;
  }//end dealerInitial()

  int Blackjack::dealerFinal() {
      int dealerSum;
      int dealerCardsArr[21];
      cout << "Dealer's first card is: ";
      dealerCardsArr[1] = dealerInitial();
      cout << "\nDealer's second card is ";
      //dealerCardsArr[1] = dealerInitial();
      dealerCardsArr[2] = pullCard();
      //cout << endl;
      dealerSum = dealerCardsArr[1] + dealerCardsArr[2];
      cout <<  " [SUM: " << dealerSum << "]" << endl;

      for (int i=3; i<21; i++) {
        if (dealerSum > 21) {
          cout << "Dealer busts with " << dealerSum << "\n\n";
          return dealerSum;
        }
        else if (dealerSum >= 17) {
          cout << "Dealer stands on " << dealerSum << "\n\n";
          return dealerSum;
        }
        else {
          cout << "Dealer hits! Card is ";
          dealerCardsArr[i] = pullCard();
          dealerSum += dealerCardsArr[i];
          cout << " [SUM: " << dealerSum << "]" << endl;

        }
      }


    return 1;
  } //end of dealerFinal()
