#include "game_loop.hpp"
#include "colors.hpp"
#include "source_dir.hpp"
#include "render.hpp"

#include <iostream>
#include <string>
#include <filesystem>


const std::filesystem::path source_dir = SourceDir::getSourceDir();

enum Actions {
	NOTHING = 0,
	EXIT = 1
};

void GameLoop::loop()
{
	bool is_alive = true;
	while (is_alive) {
		switch (mainMenu()) {
			case Actions::EXIT:
				is_alive = false;
				break;
			case Actions::NOTHING:
				break;
		}
	}
}


int GameLoop::mainMenu()
{
	render((source_dir / "assets" / "ui" / "main_menu.txt"),
			{{'@', Colors::color("bold")},
			{'$', Colors::color("reset")}});

	std::cout << Colors::color("italic dim") << "Enter the number of the option you choice" <<
		std::endl << "Or enter q/quit/exit to exit here: " << Colors::color("reset");
	std::string input;
	std::getline(std::cin, input);
	try {
		int user_choice = std::stoi(input);
		if (user_choice > 0 && user_choice <= 3) {
			std::cout << Colors::color("bold alternate") << "Coming soon" << Colors::color("reset") << std::endl <<
				 Colors::color("italic dim") << "Press Enter to return... " << Colors::color("reset");
			std::string dummy;
			std::getline(std::cin, dummy);
		}
	} catch (...) {
		if (input == "q" || input == "quit" || input == "exit") return Actions::EXIT;
	}
	return Actions::NOTHING;
}

