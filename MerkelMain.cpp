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
  currentTime = orderBook.getEarliestTime();
  wallet.insertCurrency("BTC", 10);

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
  std::cout << "Current time is " << currentTime << std::endl;
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
    std::vector<OrderBookEntry> obes = orderBook.getOrders(OrderBookType::ask, product, currentTime);
    std::cout << "Asks seen: " << obes.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(obes) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(obes) << std::endl;
  }
}

void MerkelMain::enterAsk()
{
  std::cout << "Make an ask - enter the amount; product, price, amount eg. ETC/BTC,200,0.5" << std::endl; // Sell half an ETH for 200 BTC
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3) 
  {
    std::cout << "Bad input: " << input << std::endl;
  } 
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
      if (wallet.canFulfillOrder(obe)) 
      {
        orderBook.insertOrder(obe);
        std::cout << "Wallet looks good." << std::endl;
      }
      else
        std::cout << "Insufficient funds." << std::endl;
    }
    catch(const std::exception& e)
    {
      std::cout << "MerkelMain::enterAsk Bad input. " << std::endl;
    }
  }
}

void MerkelMain::enterBid()
{
  std::cout << "Make a bid - enter the amount; product, price, amount eg. ETC/BTC,200,0.5" << std::endl; // Sell half an ETH for 200 BTC
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3) 
  {
    std::cout << "Bad input: " << input << std::endl;
  } 
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
      if (wallet.canFulfillOrder(obe)) 
      {
        orderBook.insertOrder(obe);
        std::cout << "Wallet looks good." << std::endl;
      }
      else
        std::cout << "Insufficient funds." << std::endl;
    }
    catch(const std::exception& e)
    {
      std::cout << "MerkelMain::enterAsk Bad input. " << std::endl;
    }
  }
}

void MerkelMain::printWallet()
{
  std::cout << wallet.toString() << std::endl;
}

void MerkelMain::goToNextTimeframe()
{
  std::cout << "Going to next time frame." << std::endl;
  for (std::string& p : orderBook.getKnownProducts())
  {
    std::cout << "matching " << p << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
      std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
    }
  }

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
  case 3:
    enterAsk();
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
