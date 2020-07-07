#include "OrderBook.h"
#include "CSVReader.h"
#include <set>
#include <iostream>
#include "TradingBot.h"

/** construct, reading a csv data file*/
OrderBook::OrderBook(std::string filename)
{
  orders = CSVReader::readCSV(filename);
}

/** return vector of all known products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
  std::set<std::string> productSet;

  for (OrderBookEntry& entry : orders)
  {
    productSet.insert(entry.product);
  }

  std::vector<std::string> products(productSet.begin(), productSet.end());
  return products;
}

std::vector<std::string> OrderBook::getKnownProducts(std::string timestamp)
{
  std::set<std::string> productSet;

  for (OrderBookEntry& entry : orders)
  {
    if (entry.timestamp == timestamp)
      productSet.insert(entry.product);
  }

  std::vector<std::string> products(productSet.begin(), productSet.end());
  return products;
}

/** return vector of entries according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
  std::vector<OrderBookEntry> matchingOrders;
  for (OrderBookEntry& order : orders)
  {
    if(order.orderType == type && order.product == product && order.timestamp == timestamp)
    {
      matchingOrders.push_back(order);
    }
  }
  return matchingOrders;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
  double max = orders[0].price;
  for (OrderBookEntry& e : orders)
  {
    if(e.price > max)
      max = e.price;
  }
  return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
  double min = orders[0].price;
  for (OrderBookEntry& e : orders)
  {
    if(e.price < min)
      min = e.price;
  }
  return min;
}

std::string OrderBook::getEarliestTime()
{
  return orders[0].timestamp;
}

std::string OrderBook::getLatestTime()
{
  return orders[orders.size() - 1].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
  for (OrderBookEntry& e : orders)
  {
    if(e.timestamp > timestamp)
      return e.timestamp;
  }

  return getEarliestTime();
}

std::string OrderBook::getPreviousTime(std::string timestamp)
{
  std::string previousTimestamp = "";
  for (OrderBookEntry &e : orders)
  {
    if(e.timestamp < timestamp)
      previousTimestamp = e.timestamp;
    else
      break;
  }

  return (previousTimestamp != "") ? previousTimestamp : getLatestTime();
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
  orders.push_back(order);
  std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
  std::vector<OrderBookEntry> asks, bids, sales;
  for (OrderBookEntry obe : orders)
  {
    if(obe.timestamp != timestamp || obe.product != product)
      continue;
    if (obe.orderType == OrderBookType::ask)
      asks.push_back(obe);
    if (obe.orderType == OrderBookType::bid)
      bids.push_back(obe);
  }

  // sort asks lowest first
  std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
  // sort bids highest first
  std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

  for (OrderBookEntry& ask : asks)
  {
    for (OrderBookEntry& bid : bids)
    {
      if (bid.price < ask.price || bid.amount <= 0)
        continue; // we don't have a match

      OrderBookEntry sale = OrderBookEntry(ask.price, 0, timestamp, product, OrderBookType::unknown);
      if (bid.username == TradingBot::USERNAME)
      {
        sale.username = TradingBot::USERNAME;
        sale.orderType = OrderBookType::bidsale;
      }
      if (ask.username == TradingBot::USERNAME)
      {
        sale.username = TradingBot::USERNAME;
        sale.orderType = OrderBookType::asksale;
      }

      if (bid.amount >= ask.amount) // ask is completely gone slice the bid, bid might or might not be cleared out
      {
        sale.amount = ask.amount;
        sales.push_back(sale);
        bid.amount -= ask.amount; // make sure this bid is processed correctly again if needed
        break; // go to next ask
      }
      else // bid is completely gone, slice the ask
      {
        sale.amount = bid.amount;
        sales.push_back(sale);
        ask.amount -= bid.amount;
        bid.amount = 0; // make sure this bid is not processed again
      }
    }
  }
  return sales;
}
