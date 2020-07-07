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

void TradingBot::trade()
{
  while(true)
  {
    //1. Update wallet from the transactions in the previous timeframe
    updateWallet();

    //2. check the current situation and the past entries and generate the correct orders
    generateOrders();
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
    orders.push_back(obe);
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

void TradingBot::updateWallet()
{
  std::string previousTimestamp = tradingPlatform.orderBook.getPreviousTime(tradingPlatform.currentTime);
  if (tradingPlatform.salesByTimestmap.count(previousTimestamp))
  {
    for (OrderBookEntry sale : tradingPlatform.salesByTimestmap[previousTimestamp])
    {
      if (sale.username == USERNAME)
      {
        wallet.processSale(sale);
        sales.push_back(sale);
      }
    }
  }
}

void TradingBot::generateOrders()
{

}
