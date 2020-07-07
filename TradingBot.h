#pragma once

#include "MerkelMain.h"
#include<string>
#include "Wallet.h"
#include "OrderBookEntry.h"
#include<vector>

class TradingBot
{
  public:
    TradingBot(MerkelMain& _tradingPlatform, std::string _baseCurrency, double amount);

    void logWalletContents();
    void logBidsAndAsks();
    void logSales();
    void printWallet();

    static const std::string USERNAME;

  private:
    void init();
    void generateOrder(double amount, std::string product, double price, OrderBookType type);
    void generateBid(double amount, std::string product, double price);
    void generateAsk(double amount, std::string product, double price);
    void updateWallet(OrderBookEntry &sale);

    MerkelMain &tradingPlatform;
    std::string baseCurrency;
    Wallet wallet;
    std::vector<OrderBookEntry> orders;
    std::vector<OrderBookEntry> sales;
};
