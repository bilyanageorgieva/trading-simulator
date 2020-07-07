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
  //1. Update wallet from the transactions in the previous timeframe
  updateWallet();

  //2. check the current situation and the past entries and generate the correct orders
  std::vector<std::string> knownProducts = tradingPlatform.orderBook.getKnownProducts(tradingPlatform.currentTime);
  for (std::string &product : knownProducts)
  {
    generateOrder(product);
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

void TradingBot::updateWallet()
{
  std::string previousTimestamp = tradingPlatform.orderBook.getPreviousTime(tradingPlatform.currentTime);
  if (tradingPlatform.salesByTimestmap.count(previousTimestamp) != 0)
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

double TradingBot::calculateMeanPrice(std::vector<OrderBookEntry>& orders)
{
  double sum = 0;
  for (OrderBookEntry o : orders)
  {
    sum += o.price;
  }
  return sum / orders.size();
}

double TradingBot::calculateMaxPrice(std::vector<OrderBookEntry>& orders)
{
  double max = 0;
  for (OrderBookEntry o : orders)
  {
    if (o.price > max)
      max = o.price;
  }
  return max;
}

void TradingBot::generateOrder(std::string product)
{
  std::vector<OrderBookEntry> currentAsks = tradingPlatform.orderBook.getOrders(OrderBookType::ask, product, tradingPlatform.currentTime);
  std::vector<OrderBookEntry> currentBids = tradingPlatform.orderBook.getOrders(OrderBookType::bid, product, tradingPlatform.currentTime);

  std::string previousTimestamp = tradingPlatform.orderBook.getPreviousTime(tradingPlatform.currentTime);
  std::vector<OrderBookEntry> previousAsks = tradingPlatform.orderBook.getOrders(OrderBookType::ask, product, previousTimestamp);

  double meanCurrentAsk = calculateMeanPrice(currentAsks);
  double meanPreviousAsk = calculateMeanPrice(previousAsks);

  std::vector<std::string> currs = CSVReader::tokenise(product, '/');
  if (meanCurrentAsk >= meanPreviousAsk) //prices are going up so we should buy, we should BID
  {
    // check how much of the currency we have
    double ourAmount = wallet.getBalance(currs[1]);

    if (ourAmount <= 0) // we have no money of that currency
      return;

    double price = calculateMaxPrice(currentBids) * 1.1;
    double amount = 0.2 * ourAmount;
    generateOrder(amount, product, price, OrderBookType::bid);
  }
  else //prices are going down so we should sell, we should ASK
  { 
    // check how much of the currency we have
    double ourAmount = wallet.getBalance(currs[0]);

    if (ourAmount <= 0) // we have no money of that currency
      return;

    double price = calculateMeanPrice(currentAsks);
    double amount = 0.2 * ourAmount;
    generateOrder(amount, product, price, OrderBookType::ask);
  }
}
