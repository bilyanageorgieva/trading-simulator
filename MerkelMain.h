#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
  public:
    /**
     * Initializes a new Merkelmain instance and starts the simulator.
     * 
     * @return the new instance
    */
    MerkelMain();

    /** 
     * Moves to the next timeframe and matches the asks with the bids. 
     * If there is no next timeframe, moves back to the first one 
     * */
    void goToNextTimeframe();

    /** The current time of the simulator */
    std::string currentTime;
    /** The order book of the simulator */
    OrderBook orderBook{"trading.csv"};
    /** All the sales mapped by timestamp */
    std::map<std::string, std::vector<OrderBookEntry>> salesByTimestmap;

  private:
    void init();
    void printMarketStats();
};
