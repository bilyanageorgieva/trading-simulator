#include <iostream>

void processOption(int option)
{
  switch (option)
    {
      case 1:
        std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
        break;

      case 2:
        std::cout << "Market looks good!" << std::endl;
        break;

      case 3:
        std::cout << "Make an offer - enter the amount" << std::endl;
        break;

      case 4:
        std::cout << "Make a bid" << std::endl;
        break;

      case 5:
        std::cout << "Your wallet is empty." << std::endl;
        break;

      case 6:
        std::cout << "Going to next time frame." << std::endl;
        break;
      
      default:
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
        break;
    }
}

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

int main()
{
  while (true)
  {
    printMenu();

    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;

    processOption(userOption);

    std::cout << std::endl;
  }

  return 0;
}
