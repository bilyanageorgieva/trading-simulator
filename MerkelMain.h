#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
  public:
    MerkelMain();
    /** Call this to start the simulator */
    void init();
  
  private:
    void loadOrderBook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void goToNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    OrderBook orderBook{"trading.csv"};
};
