#include "TradingBot.h"
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include<iostream>

const std::string TradingBot::USERNAME = "TradingBot";

TradingBot::TradingBot(MerkelMain& _tradingPlatform, std::string _baseCurrency, double amount)
  : tradingPlatform(_tradingPlatform), baseCurrency(_baseCurrency)
{
  wallet = Wallet();
  wallet.insertCurrency(_baseCurrency, amount);
}

void TradingBot::init()
{
  while(true)
  {
    //do something
  }
}

void TradingBot::logWalletContents()
{
  std::cout << wallet.toString() << std::endl;
}

void TradingBot::logBidsAndAsks()
{
  for (OrderBookEntry& obe : orders)
  {
    std::cout << obe.toString() << std::endl;
  }
}

void TradingBot::logSales()
{
  for (OrderBookEntry& sale : sales)
  {
    std::cout << sale.toString() << std::endl;
  }
}

void TradingBot::printWallet()
{
  std::cout << wallet.toString() << std::endl;
}

void TradingBot::generateOrder(double amount, std::string product, double price, OrderBookType type)
{
  OrderBookEntry obe = OrderBookEntry(price, 
                                        amount, 
                                        tradingPlatform.currentTime, 
                                        product, 
                                        type,
                                        USERNAME);
  if (wallet.canFulfillOrder(obe))
  {
    tradingPlatform.orderBook.insertOrder(obe);
    std::cout << "Wallet looks good." << std::endl;
  }
  else
    std::cout << "Insufficient funds." << std::endl;
}

void TradingBot::generateBid(double amount, std::string product, double price)
{
  generateOrder(amount, product, price, OrderBookType::bid);
}

void TradingBot::generateAsk(double amount, std::string product, double price)
{
  generateOrder(amount, product, price, OrderBookType::ask);
}

void TradingBot::updateWallet(OrderBookEntry& sale)
{
  wallet.processSale(sale);
}