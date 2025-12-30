#include "render.hpp"
#include "colors.hpp"

#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <fstream>
#include <stdexcept>


std::string readTemplate(const std::filesystem::path& template_path)
{
	std::ifstream file(template_path);
	if (!file.is_open()) {
		throw std::invalid_argument(Colors::color("error") + "Fatal: file [" +
			template_path.filename().string() + "] not found" + Colors::color("reset"));
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string result = buffer.str();
	return result;
}


// Menus render
void render(const std::filesystem::path& template_path,
		const std::unordered_map<char, std::string>& replace_symbols)
{
	std::string render_template = readTemplate(template_path);

	std::cout << Colors::color("clear");
	for (const char& symbol : render_template) {
		if (auto iter = replace_symbols.find(symbol); iter != replace_symbols.end()) {
			std::cout << iter->second << ' ';
		} else std::cout << symbol;
	}
}
