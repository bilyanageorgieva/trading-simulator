#include "OrderBookEntry.h"
#include <iomanip>
#include <sstream>

OrderBookEntry::OrderBookEntry(double price,
                               double amount,
                               std::string timestamp,
                               std::string product,
                               OrderBookType orderType,
                               std::string username)
    : price(price), amount(amount), timestamp(timestamp), product(product), orderType(orderType), username(username){};

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
    return OrderBookType::ask;
  if (s == "bid")
    return OrderBookType::bid;
  else
    return OrderBookType::unknown;
}

std::string OrderBookEntry::toString()
{
  std::string type;
  switch (orderType)
  {
  case OrderBookType::bid:
    type = "Bid";
    break;
  case OrderBookType::ask:
    type = "Ask";
    break;
  case OrderBookType::bidsale:
    type = "Bid sale";
    break;
  case OrderBookType::asksale:
    type = "Ask sale";
    break;
  default:
    type = "Unknown";
    break;
  }

  std::stringstream amount_stream;
  amount_stream << std::fixed << std::setprecision(8) << amount;

  std::stringstream price_stream;
  price_stream << std::fixed << std::setprecision(8) << price;

  return timestamp + " Type: " + type + " Product: " + product + " Price: " + price_stream.str() + " Amount: " + amount_stream.str() + " Username: " + username;
}
