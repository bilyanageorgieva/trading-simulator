#include "MerkelMain.h"
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
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
  std::cout << "5: Print wallet" << std::endl;
  std::cout << "6: Continue" << std::endl;

  // prompt user to select an option
  std::cout << "===================== " << std::endl;
  std::cout << "Type in 1-6" << std::endl;
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
    std::vector<OrderBookEntry> obes = orderBook.getOrders(OrderBookType::ask, product, "2020/03/17 17:01:24.884492");
    std::cout << "Asks seen: " << obes.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(obes) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(obes) << std::endl;
  }
}

void MerkelMain::enterOffer()
{
  std::cout << "Make an offer - enter the amount" << std::endl;
}

void MerkelMain::enterBid()
{
  std::cout << "Make a bid" << std::endl;
}

void MerkelMain::printWallet()
{
  std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::goToNextTimeframe()
{
  std::cout << "Going to next time frame." << std::endl;
}

int MerkelMain::getUserOption()
{
  int userOption;
  std::cin >> userOption;
  std::cout << "You chose: " << userOption << std::endl;
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
  case 3:
    enterOffer();
    break;
  case 4:
    enterBid();
    break;
  case 5:
    printWallet();
    break;
  case 6:
    goToNextTimeframe();
    break;
  default:
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
    break;
  }
}
