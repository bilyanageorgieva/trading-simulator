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
    void goToNextTimeframe();

    std::string currentTime;
    OrderBook orderBook{"trading.csv"};
    std::map<std::string, std::vector<OrderBookEntry>> salesByTimestmap;

  
  private:
    void loadOrderBook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    int getUserOption();
    void processUserOption(int userOption);
};
