#include "Wallet.h"
#include "CSVReader.h"
#include <iostream>

Wallet::Wallet(){}

void Wallet::insertCurrency(std::string type, double amount)
{
  if (amount < 0)
  {
    throw std::exception{};
  }

  if (currencies.count(type) == 0)
  {
    currencies[type] = amount;
  }
  else 
  {
    currencies[type] += amount;
  }
}

bool Wallet::removeCurrency(std::string type, double amount)
{
  if (amount < 0 || !containsCurrency(type, amount))
    return false;
  
  currencies[type] -= amount;
  return true;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
  if (currencies.count(type) == 0)
    return false;
  else
    return currencies[type] >= amount;
}

bool Wallet::canFulfillOrder(OrderBookEntry order)
{
  std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
  if (order.orderType == OrderBookType::ask)
  {
    double amount = order.amount;
    std::string currency = currs[0];
    std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
    return containsCurrency(currency, amount);
  }
  if (order.orderType == OrderBookType::bid)
  {
    double amount = order.amount * order.price;
    std::string currency = currs[1];
    std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
    return containsCurrency(currency, amount);
  }
  return false;
}

std::string Wallet::toString()
{
  std::string s;
  for (std::pair<std::string, double> pair : currencies)
  {
    std::string currency = pair.first;
    double amount = pair.second;
    s += currency + " : " + std::to_string(amount) + "\n";
  }
  return s;
}
