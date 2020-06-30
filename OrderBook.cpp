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
