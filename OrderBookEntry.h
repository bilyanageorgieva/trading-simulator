#pragma once

#include <string>

enum class OrderBookType
{
  bid,
  ask,
  asksale,
  bidsale,
  unknown
};

class OrderBookEntry
{
public:
  /**
   * Initializes a new instance.
   * 
   * @param price the price of the order
   * @param amount the amount of the product
   * @param timestamp the timestamp of the order
   * @param product the product of the order
   * @param orderType the type of the order
   * @param username the username of the user that made the order
   * @return the new order
  */
  OrderBookEntry(double price,
                 double amount,
                 std::string timestamp,
                 std::string product,
                 OrderBookType orderType,
                 std::string username = "dataset");

  /**
   * Converts a string to an order book type
   * 
   * @param str the string to convert
   * @return the matching order book type
  */
  static OrderBookType stringToOrderBookType(std::string str);

  /**
   * Creates a string representation of the order.
   * 
   * @return the string representation of the order
  */
  std::string toString();

  /**
   * Compares two orders by their timestamp.
   * 
   * @param e1 the first order to compare
   * @param e2 the second order to compare
   * @return true if the first order has a smaller timestamp that the secoond, false otherwise
  */
  static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

  /**
   * Compares two orders by their price in ascending order.
   * 
   * @param e1 the first order to compare
   * @param e2 the second order to compare
   * @return true if the first order has a smaller price that the secoond, false otherwise
  */
  static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

  /**
   * Compares two orders by their price in descending order.
   * 
   * @param e1 the first order to compare
   * @param e2 the second order to compare
   * @return true if the first order has a bigger price that the secoond, false otherwise
  */
  static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

  /** The price of the order */ 
  double price;
  /** The amount of the product */
  double amount;
  /** The timestamp of the order */
  std::string timestamp;
  /** The product of the order*/
  std::string product;
  /** The type of the order */
  OrderBookType orderType;
  /** The username of the user that created the order */
  std::string username;
};