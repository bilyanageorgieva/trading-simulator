#pragma once

#include <vector>
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
  public:
    Wallet();

    /** Insert a currency into the wallet */
    void insertCurrency(std::string type, double amount);

    /** Remove a currency from the wallet */
    bool removeCurrency(std::string type, double amount);

    /** Check if the wallet contains this amount of the currency or more */
    bool containsCurrency(std::string type, double amount);

    /** Check if the wallet can cope with this ask or bid */
    bool canFulfillOrder(OrderBookEntry order);

    /** Generate the string representation of the wallet */
    std::string toString();

  private:
    std::map<std::string, double> currencies;
};