#include "game_loop.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <filesystem>


enum Actions {
	NOTHING = 0,
	EXIT = 1
};

void GameLoop::loop()
{
	std::string MAIN_MENU_TEMPLATE = Utils::readFile("assets/ui/main_menu.txt");
	bool is_alive = true;
	while (is_alive) {
		switch (mainMenu(MAIN_MENU_TEMPLATE)) {
			case Actions::EXIT:
				is_alive = false;
				break;
			case Actions::NOTHING:
				break;
		}
	}
}


int GameLoop::mainMenu(std::string &menu_template)
{
	std::cout << "\033c";
	for (char symbol : menu_template) {
		if (symbol == '@' || symbol == '$') std::cout << ' ';
		else std::cout << symbol;
	}
	std::cout << "\033[2;3mEnter the number of the option you choice" <<
		std::endl << "Or enter q/quit/exit to exit here: \033[0m";
	std::string input;
	std::getline(std::cin, input);
	try {
		int user_choice = std::stoi(input);
		if (user_choice > 0 && user_choice <= 3) {
			std::cout << "\033[1;34mComing soon\033[0m" <<
				std::endl << "\033[2;3mPress Enter to return... ";
			std::cin.get();
		}
	} catch (...) {
		if (input == "q" || input == "quit" || input == "exit") return Actions::EXIT;
	}
	return Actions::NOTHING;
}

