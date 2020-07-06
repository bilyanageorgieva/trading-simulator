#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
  std::vector<OrderBookEntry> entries;
  std::string line;
  std::ifstream csvFile{csvFileName};

  if (csvFile.is_open())
  {
    while (std::getline(csvFile, line))
    {
      try
      {
        OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
        entries.push_back(obe);
      }
      catch(const std::exception& e)
      {
        std::cout << "CSVReader: Bad data!" << std::endl;
      }
    }

    csvFile.close();
  }

  return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
  std::vector<std::string> tokens;
  signed int start, end;
  start = csvLine.find_first_not_of(separator, 0);

  do {
    end = csvLine.find_first_of(separator, start);

    if (start == csvLine.length() || start == end) break;
    if (end >= 0) tokens.push_back(csvLine.substr(start, end-start));
    else tokens.push_back(csvLine.substr(start, csvLine.length() - start));

    start = end + 1;
  } while (end > 0);

  return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType type)
{
  double price, amount;

  try
  {
    price = std::stod(priceString);
    amount = std::stod(amountString);
  }
  catch (const std::exception &e)
  {
    std::cout << "Bad float!" << std::endl;
    throw;
  }

  OrderBookEntry obe {price, amount, timestamp, product, type};
  return obe;
}


OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
  if (tokens.size() != 5)
  {
    std::cout << "Bad line!" << std::endl;
    throw std::exception{};
  }

  return stringsToOBE(tokens[3], tokens[4], tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2]));
}