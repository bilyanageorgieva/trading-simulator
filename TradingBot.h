#pragma once

#include "MerkelMain.h"
#include<string>
#include "Wallet.h"
#include "OrderBookEntry.h"
#include<vector>

class TradingBot
{
  public:
    /**
     * Initializes a new instance.
     * 
     * @param _tradingPlatform the MerkelMain trading platform on which the bot should trade
     * @param currency the initial currency that the bot will have in its wallet
     * @param amount the initial amount that the bot will have in its wallet
     * @return a new TradingBot instance
    */
    TradingBot(MerkelMain& _tradingPlatform, std::string currency, double amount);
    
    /** The bot places all of its bids and asks for the current timestamp */
    void trade();

    /** The bot logs all the contents of its wallet */
    void logWalletContents();

    /** The bot logs all of its bids and asks */
    void logBidsAndAsks();

    /** The bot logs all of the sales it took part in */
    void logSales();

    /** The username that the bot will use for his offers */     
    static const std::string USERNAME;

  private:
    void updateWallet();
    double calculateMeanPrice(std::vector<OrderBookEntry>& orders);
    double calculateMaxPrice(std::vector<OrderBookEntry>& orders);
    void generateOrder(double amount, std::string product, double price, OrderBookType type);
    void generateOrder(std::string product);

    MerkelMain& tradingPlatform;
    Wallet wallet;
    std::vector<OrderBookEntry> orders;
    std::vector<OrderBookEntry> sales;
};
