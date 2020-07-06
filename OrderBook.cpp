#include "OrderBook.h"
#include "CSVReader.h"
#include <set>
#include <iostream>

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

std::string OrderBook::getNextTime(std::string timestamp)
{
  for (OrderBookEntry& e : orders)
  {
    if(e.timestamp > timestamp)
      return e.timestamp;
  }

  return getEarliestTime();
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

  for (OrderBookEntry& ask : asks)
  {
    for (OrderBookEntry& bid : bids)
    {
      if (bid.price < ask.price)
        continue; // we don't have a match

      if (bid.amount >= ask.amount) // ask is completely gone slice the bid, bid might or might not be cleared out
      {
        OrderBookEntry sale = OrderBookEntry(ask.price, ask.amount, timestamp, product, OrderBookType::sale);
        sales.push_back(sale);
        bid.amount -= ask.amount; // make sure this bid is processed correctly again if needed
        break; // go to next ask
      }
      else 
      {
        OrderBookEntry sale = OrderBookEntry(ask.price, bid.amount, timestamp, product, OrderBookType::sale);
        sales.push_back(sale);
        ask.amount -= bid.amount;
        bid.amount = 0; // make sure this bid is not processed again
      }
    }
  }
  return sales;
}
