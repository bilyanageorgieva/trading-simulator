#include "OrderBookEntry.h"
#include <string>
#include <iomanip>
#include <sstream>

OrderBookEntry::OrderBookEntry(double price,
                               double amount,
                               std::string timestamp,
                               std::string product,
                               OrderBookType orderType,
                               std::string username)
    : price(price), amount(amount), timestamp(timestamp), product(product), orderType(orderType), username(username){};

OrderBookType OrderBookEntry::stringToOrderBookType(std::string str)
{
  if (str == "ask")
    return OrderBookType::ask;
  if (str == "bid")
    return OrderBookType::bid;
  else
    return OrderBookType::unknown;
}

std::string OrderBookEntry::toString()
{
  std::string typeString;

  switch (orderType)
  {
  case OrderBookType::bid:
    typeString = "Bid";
    break;
  case OrderBookType::ask:
    typeString = "Ask";
    break;
  case OrderBookType::bidsale:
    typeString = "Bid sale";
    break;
  case OrderBookType::asksale:
    typeString = "Ask sale";
    break;
  default:
    typeString = "Unknown";
    break;
  }

  std::stringstream amount_stream;
  amount_stream << std::fixed << std::setprecision(8) << amount;

  std::stringstream price_stream;
  price_stream << std::fixed << std::setprecision(8) << price;

  return timestamp + " Type: " + typeString + " Product: " + product + " Price: " + price_stream.str() + " Amount: " + amount_stream.str() + " Username: " + username;
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.price > e2.price;
}
