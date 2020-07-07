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
  }
}
