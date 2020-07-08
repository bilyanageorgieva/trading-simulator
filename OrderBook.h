#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
  public:
    /** 
     * Construct, reading a csv data file
     * 
     * @param filename the name of the csv file
     * @return a new order book instance with the data from the csv file
     * */
    OrderBook(std::string filename);

    /** 
     * Create a vector of all known products in the dataset
     * 
     * @return the vector of all products known for all timestamps
     * */
    std::vector<std::string> getKnownProducts();

    /**
     * Create a vector of all known products in the dataset for a specific timestamp
     * 
     * @param timestamp the timestamp for which to check the products
     * @return the vector of all products known for the given timestamps
    */
    std::vector<std::string> getKnownProducts(std::string timestamp);

    /** 
     * Creates a vector of orders according to the sent filters
     * 
     * @param type the type of the orders
     * @param product the product of the orders
     * @param timestamp the timestamp of the orders
     * @return a vector of all matching orders
     * */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

    /** 
     * Gets the earliest time in the orderbook
     * 
     * @return the earliest time seen in the orderbook
     * */  
    std::string getEarliestTime();

    /**
     * Gets the last time in the orderbook
     * 
     * @return the last time seen in the orderbook
    */
    std::string getLatestTime();

    /** 
     * Gets the next time after the sent time in the orderbook
     * If there is no next timestamp, wraps around and returns the earliest time.
     * 
     * @param timestamp the timestamp to use as a base
     * @return the timestamp right after the given one, or the first one if missing
     * */ 
    std::string getNextTime(std::string timestamp);

    /**
     * Gets the next time before the sent time in the orderbook
     * If there is no previous timestamp, wraps around and returns the last time.
     * 
     * @param timestamp the timestamp to use as a base
     * @return the timestamp right before the given one, or the last one if missing
    */
    std::string getPreviousTime(std::string timestamp);

    /**
     * Inserts an order into the orderbook
     * 
     * @param order the order to insert
    */
    void insertOrder(OrderBookEntry& order);

    /**
     * Matches the asks with the bids for a specific prrooduct and timestamp
     * 
     * @param product the product whose orders to match
     * @param timestamp the timestamp for which to match
     * @return the vector of all successful sales
    */
    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    /**
     * Gets the price of the order with the highest price from a list of orders
     * 
     * @param orders the list of orders 
     * @return the price of the order with the highest price
    */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);

    /**
     * Gets the price of the order with the lowest price from a list of orders
     * 
     * @param orders the list of orders 
     * @return the price of the order with the lowest price
    */
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

  private:
    std::vector<OrderBookEntry> orders;
};