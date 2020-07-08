#pragma once

#include "OrderBookEntry.h"
#include<vector>
#include<string>

class CSVReader
{
  public:
    /** Initializes a new CSVReader instance */
    CSVReader();

    /**
     * Reads a CSV file and transforms it into a vector of all OrderBookEntries present
     * 
     * @param csvFile the name of the csv file to read
     * @return a vector of the OrderBookEntries found
    */
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    /**
     * Separates a string into parts based on a separator
     * 
     * @param csvLine the string/csv line to separate
     * @param separator the symbol with which the different parts are separated in the string
     * @return a vector of the different parts in order seen
    */
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    /**
     * Converts a set of string values into an OrderBookEntry
     * 
     * @param price the string representation of the price of the order
     * @param amount the string representation of the amount of the order
     * @param timestamp the timestamp of the order
     * @param product the product of the order
     * @param type the type of the order
     * @return the created order
    */
    static OrderBookEntry stringsToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType type);

  private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};