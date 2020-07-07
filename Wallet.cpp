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

void Wallet::processAskSale(OrderBookEntry& sale)
{
  std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

  double outgoingAmount = sale.amount;
  std::string outgoingCurrency = currs[0];
  double incomingAmount = sale.amount * sale.price;
  std::string incomingCurrency = currs[1];

  insertCurrency(incomingCurrency, incomingAmount);
  // removeCurrency(outgoingCurrency, outgoingAmount);
  currencies[outgoingCurrency] -= outgoingAmount;
}

void Wallet::processBidSale(OrderBookEntry& sale)
{
  std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

  double incomingAmount = sale.amount;
  std::string incomingCurrency = currs[0];
  double outgoingAmount = sale.amount * sale.price;
  std::string outgoingCurrency = currs[1];

  insertCurrency(incomingCurrency, incomingAmount);
  // removeCurrency(outgoingCurrency, outgoingAmount);
  currencies[outgoingCurrency] -= outgoingAmount;
  
}

void Wallet::processSale(OrderBookEntry& sale)
{
  if (sale.orderType == OrderBookType::bidsale)
    processBidSale(sale);
  if (sale.orderType == OrderBookType::asksale)
    processAskSale(sale);
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

std::ostream& operator<<(std::ostream& os,  Wallet& wallet)
{
    os << wallet.toString();
    return os;
}
