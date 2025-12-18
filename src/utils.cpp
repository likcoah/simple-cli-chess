#include "utils.hpp"
#include "source_dir.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>


std::filesystem::path source_dir = SourceDir::getSourceDir();

std::string Utils::read_file(const std::filesystem::path &relative_file_path)
{
	std::filesystem::path file_path = source_dir / relative_file_path;
	std::ifstream file(file_path);
	if (!file.is_open()) {
		std::cerr << "Fatal: file " << file_path.filename() << " not found" << std::endl;
		throw std::invalid_argument("File not found");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string result = buffer.str();
	file.close();
	return result;
}
