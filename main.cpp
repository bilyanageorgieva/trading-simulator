#include <iostream>
#include <string>
#include <vector>
#include "MerkelMain.h"
#include "TradingBot.h"


int main()
{
  MerkelMain app{};
  app.init();
  TradingBot bot = TradingBot(app, "BTC", 10);

  while(true)
  {
    bot.trade();
    app.goToNextTimeframe();

    std::cout << std::endl << "----------------- BIDS & ASKS -----------------" << std::endl;
    bot.logBidsAndAsks();

    std::cout << std::endl << "----------------- SALES -----------------" << std::endl;
    bot.logSales();

    std::cout << std::endl << "----------------- WALLET -----------------" << std::endl;
    bot.logWalletContents();
  }
}
