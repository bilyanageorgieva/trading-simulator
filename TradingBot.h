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

    void trade();
    void logWalletContents();
    void logBidsAndAsks();
    void logSales();

    static const std::string USERNAME;

  private:
    void updateWallet();
    double calculateMeanPrice(std::vector<OrderBookEntry>& orders);
    double calculateMaxPrice(std::vector<OrderBookEntry>& orders);
    void generateOrder(double amount, std::string product, double price, OrderBookType type);
    void generateOrder(std::string product);

    MerkelMain& tradingPlatform;
    std::string baseCurrency;
    Wallet wallet;
    std::vector<OrderBookEntry> orders;
    std::vector<OrderBookEntry> sales;
};
