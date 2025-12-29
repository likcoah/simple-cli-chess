#include "colors.hpp"
#include "source_dir.hpp"

#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
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
		{"black_piece", "red"},
		{"success", "green"},
		{"error", "red"},
		{"alternate", "blue"}
	};
	stylemap colors = {
		{"black", "0"},
		{"red", "1"},
		{"green", "2"},
		{"yellow", "3"},
		{"blue", "4"},
		{"purple", "5"},
		{"cyan", "6"},
		{"white", "7"}
	};
	stylemap styles = {
		{"bold", "1"},
		{"dim", "2"},
		{"italic", "3"},
		{"underline", "4"},
		{"inverse", "7"},
		{"strikethrough", "8"},
	};
	stylemap layers = {
		{"background", "bg"},
		{"foreground", "fg"},
		{"square_light", "bg"},
		{"square_dark", "bg"},
		{"last_move", "bg"},
		{"check", "bg"},
		{"white_piece", "fg"},
		{"black_piece", "fg"},
		{"success", "fg"},
		{"error", "fg"},
		{"alternate", "fg"}
	};



	void reset()
	{
		*this = StyleConfig();
	}
	void reset(stylemap StyleConfig::*field)
	{
		this->*field = StyleConfig().*field;
	}



	static bool existsWithContent(const std::filesystem::path &file_path)
	{
		return std::filesystem::exists(file_path) &&
			!std::filesystem::is_empty(file_path);
	}


	static std::string colorLayerConvert(const std::string &color_layer) {
		if (color_layer == "bg") return "4";
		else if (color_layer == "fg") return "3";
		else throw std::invalid_argument("invalid color layer");
	}


	void initStyleConfig()
	{
		static bool initialized = false;
		if (initialized) return;

		const std::filesystem::path source_dir = SourceDir::getSourceDir(),
			  options_path = source_dir / "res" / "options.txt";

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



		const std::filesystem::path format_path = source_dir / "res" / "themes" / (name + ".txt"),
			colors_path = source_dir / "res" / "themes" / "colors" / (name + ".txt");

		if (!existsWithContent(format_path)) { reset(); return; }

		if (std::ifstream format_data(format_path); format_data) {
			for (std::string layer, format_name, value; format_data >> layer >> format_name >> value; ) {
				format[format_name] = value;
				layers[format_name] = layer;
			}
		} else { reset(); return; }
		


		if (!existsWithContent(colors_path)) { reset(&StyleConfig::colors); return; }
		else if (std::ifstream colors_data(colors_path); colors_data) {
			for (std::string color_name, r, g, b; colors_data >> color_name >> r >> g >> b; ) {
				colors[color_name] = "8;2;" + r + ";" + g + ";" + b;
			}
		} else reset(&StyleConfig::colors);

		initialized = true;
	}
};


namespace Colors
{
	std::string color(std::string style_tags)
	{
		if (style_tags == "reset") return "\033[0m";
	
	
		static StyleConfig config;
		config.initStyleConfig();
	
	
		std::string styles, colors;
	
		if (std::stringstream style_tags_stream(style_tags); style_tags_stream) {
			for (std::string tag; style_tags_stream >> tag; ) {
				if (auto iter_style = config.styles.find(tag); iter_style != config.styles.end()) {
					styles += iter_style->second + ";";
				} else if (auto iter_format = config.format.find(tag); iter_format != config.format.end()) {
					if (auto iter_color = config.colors.find(iter_format->second); iter_color != config.colors.end()) {
						colors += StyleConfig::colorLayerConvert(config.layers[iter_format->first]) + iter_color->second + ";";
					}
				} else throw std::invalid_argument("invalid style tag");
			}
		}
	
		
		std::string result;
		result += styles + colors;
		if (!result.empty()) result.pop_back();
		else throw std::invalid_argument("invalid style tag");
		return "\033[" + result + "m";
	}
}

