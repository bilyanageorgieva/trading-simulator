#include <iostream>

void printMenu()
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

int selectOption()
{
  int userOption;
  std::cin >> userOption;
  std::cout << "You chose: " << userOption << std::endl;
  return userOption;
}

void printHelp()
{
  std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void printExchangeStats()
{
  std::cout << "Market looks good!" << std::endl;
}

void makeOffer()
{
  std::cout << "Make an offer - enter the amount" << std::endl;
}

void makeBid()
{
  std::cout << "Make a bid" << std::endl;
}

void printWallet()
{
  std::cout << "Your wallet is empty." << std::endl;
}

void nextTimeframe()
{
  std::cout << "Going to next time frame." << std::endl;
}



void processOption(int option)
{
  switch (option)
    {
      case 1: printHelp(); break;
      case 2: printExchangeStats(); break;
      case 3: makeOffer(); break;
      case 4: makeBid(); break;
      case 5: std::cout << "Your wallet is empty." << std::endl; break;
      case 6: std::cout << "Going to next time frame." << std::endl; break;
      default: std::cout << "Invalid choice. Choose 1-6" << std::endl; break;
    }
}

int main()
{
  while (true)
  {
    printMenu();
    int userOption = selectOption();
    processOption(userOption);
  }

  return 0;
}
