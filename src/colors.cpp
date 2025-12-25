#include "colors.hpp"
#include "source_dir.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>


struct StyleConfig
{
	using stylemap = std::unordered_map<std::string, std::string>;

	std::string name = "Default";
	stylemap format = {
		{"background", "black"},
		{"foreground", "white"},
		{"square_light", "white"},
		{"square_dark", "black"},
		{"last_move", "cyan"},
		{"check", "green"},
		{"white_piece", "blue"},
		{"black_piece", "red"}
	};
	stylemap colors = {
		{"black", "0;"},
		{"red", "1;"},
		{"green", "2;"},
		{"yellow", "3;"},
		{"blue", "4;"},
		{"purple", "5;"},
		{"cyan", "6;"},
		{"white", "7;"}
	};
	stylemap styles = {
		{"bold", "1;"},
		{"dim", "2;"},
		{"italic", "3;"},
		{"underline", "4;"},
		{"inverse", "7;"},
		{"strikethrough", "8;"},
	};



	void reset()
	{
		*this = StyleConfig();
	}
	void reset(stylemap StyleConfig::*field)
	{
		this->*field = StyleConfig().*field;
	}



	static bool existsWithContent(const std::filesystem::path file_path)
	{
		return std::filesystem::exists(file_path) &&
			!std::filesystem::is_empty(file_path);
	}



	void initStyleConfig()
	{
		const std::filesystem::path source_dir = SourceDir::getSourceDir(),
			  options_path = source_dir / "res/options.txt";

		if (!existsWithContent(options_path)) return;

		if (std::ifstream options(options_path); options) {
			std::string theme_name;
			for (std::string option_name, option_value; options >> option_name >> option_value; ) {
				if (option_name == "THEME") {
					theme_name = option_value;
				}
			}
			if (theme_name.empty()) {
				reset();
				return;
			} else name = theme_name;
		} else { reset(); return; }



		const std::filesystem::path format_path = source_dir / ("res/themes/" + name + ".txt"),
			colors_path = source_dir / ("res/themes/colors/" + name + ".txt");

		if (!existsWithContent(format_path)) { reset(); return; }

		if (std::ifstream format_data(format_path); format_data) {
			for (std::string name, value; format_data >> name >> value; ) {
				format[name] = value;
			}
		} else { reset(); return; }
		


		if (!existsWithContent(colors_path)) { reset(&StyleConfig::colors); return; }

		if (std::ifstream colors_data(colors_path); colors_data) {
			for (std::string name, r, g, b; colors_data >> name >> r >> g >> b; ) {
				colors[name] = "38;2;" + r + ";" + g + ";" + b + ";";
			}
		} else { reset(&StyleConfig::colors); return; }
	}
};


std::string Colors::color(std::string style_tags)
{
	static StyleConfig config;
	config.initStyleConfig();

	return "";
}

