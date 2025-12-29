#include <iostream>
#include <string>

int main()
{
    std::cout << "=========================================\n";
    std::cout << "      THE ANCIENT RELIC – TOMB CRAWLER\n";
    std::cout << "=========================================\n\n";

    std::cout << "The ancient relic that keeps the land alive has been stolen.\n";
    std::cout << "Crops are dying. Rivers are drying.\n";
    std::cout << "An evil Goblin King has taken it into the underground tombs.\n\n";

    std::cout << "You are the last warrior.\n";
    std::cout << "Your mission is to enter the tombs, defeat the goblins,\n";
    std::cout << "and return the relic to save the world.\n\n";

    std::cout << "Press ENTER to begin your journey...";
    std::string input;
    std::getline(std::cin, input);

    std::cout << "\nYour adventure begins...\n";

    return 0;
}
