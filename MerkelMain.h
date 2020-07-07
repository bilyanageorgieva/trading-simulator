#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

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
    void enterAsk();
    void enterBid();
    void printWallet();
    void goToNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    void processSale(OrderBookEntry& sale);

    std::string currentTime;
    OrderBook orderBook{"trading.csv"};
    Wallet wallet;
};
