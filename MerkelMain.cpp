#include "MerkelMain.h"
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "TradingBot.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
  currentTime = orderBook.getEarliestTime();

  loadOrderBook();
  while (true)
  {
    printMenu();
    int userOption = getUserOption();
    processUserOption(userOption);
  }
}

void MerkelMain::loadOrderBook()
{
}

void MerkelMain::printMenu()
{
  // print menu
  std::cout << "1: Print help" << std::endl;
  std::cout << "2: Print exchange stats" << std::endl;
  std::cout << "3: Make an offer" << std::endl;
  std::cout << "4: Make a bid" << std::endl;
  std::cout << "5: Continue" << std::endl;

  // prompt user to select an option
  std::cout << "===================== " << std::endl;
  std::cout << "Current time is " << currentTime << std::endl;
  std::cout << "Type in 1-5" << std::endl;
}

void MerkelMain::printHelp()
{
  std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
  for (std::string const product : orderBook.getKnownProducts())
  {
    std::cout << "Product: " << product << std::endl;
    std::vector<OrderBookEntry> obes = orderBook.getOrders(OrderBookType::ask, product, currentTime);
    std::cout << "Asks seen: " << obes.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(obes) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(obes) << std::endl;
  }
}

void MerkelMain::goToNextTimeframe()
{
  std::cout << "Going to next time frame." << std::endl;
  std::vector<OrderBookEntry> successfulSales;
  for (std::string &p : orderBook.getKnownProducts())
  {
    std::cout << "matching " << p << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
      std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
      successfulSales.push_back(sale);
    }
  }

  salesByTimestmap[currentTime] = successfulSales;
  currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
  int userOption = 0;
  std::string line;
  std::getline(std::cin, line);
  try
  {
    userOption = std::stoi(line);
    std::cout << "You chose: " << userOption << std::endl;
  }
  catch(const std::exception& e)
  {
    //
  }
  return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
  switch (userOption)
  {
  case 1:
    printHelp();
    break;
  case 2:
    printMarketStats();
    break;
  case 5:
    goToNextTimeframe();
    break;
  default:
    std::cout << "Invalid choice. Choose 1-5" << std::endl;
    break;
  }
}
