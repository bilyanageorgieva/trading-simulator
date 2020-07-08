#pragma once

#include <vector>
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
  public:
    /**
     * Initializes a new Wallet instance.
     * 
     * @return the newly created empty wallet
    */
    Wallet();

    /** 
     * Insert a currency into the wallet 
     * 
     * @param type the type of currency to insert
     * @param amount the amount of the specified currency to insert
     * */
    void insertCurrency(std::string type, double amount);

    /** 
     * Remove a currency from the wallet 
     * 
     * @param type the type of currency to remove
     * @param amount the amount of the specified currency to remove
     * @return true if the operation was successful, false otherwise
     * */
    bool removeCurrency(std::string type, double amount);

    /** 
     * Check if the wallet contains this amount of the currency or more 
     * 
     * @param type the type of currency to check for
     * @param amount the amount of the specified currency to check for
     * @return true if the operation was successful, false otherwise
     * */
    bool containsCurrency(std::string type, double amount);
    
    /**
     * Gets the amount that the wallet contains for a specific currency.
     * 
     * @param currency the currency to check for
     * @return the amount of this currency that is present in the wallet
    */
    double getBalance(std::string currency);

    /** 
     * Check if the wallet can cope with this ask or bid 
     * 
     * @param order the OrderBookEntry to check if it can be fulfilled
     * @return true if the order can be fulfilled, false otherwise
     * */
    bool canFulfillOrder(OrderBookEntry& order);

    /** 
     * Applies the necessary changes to the balance after a successful sale
     * 
     * @param sale the sale that succeeded
     * @return true if the operation was successful, false otherwise
    */
    void processSale(OrderBookEntry& sale);

    /** 
     * Generate the string representation of the wallet 
     * 
     * @return the string representation of the wallet
     * */
    std::string toString();

  private:
    /** Process an ask sale of the user */
    void processAskSale(OrderBookEntry& sale);

    /** Process a bid sale of the user */
    void processBidSale(OrderBookEntry& sale);

    std::map<std::string, double> currencies;
};