#include "MerkelMain.h"
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "TradingBot.h"

MerkelMain::MerkelMain()
{
  init();
}

void MerkelMain::init()
{
  currentTime = orderBook.getEarliestTime();
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
    std::cout << "Matching " << p << std::endl;
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
