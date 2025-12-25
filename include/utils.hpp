#pragma once

#include <filesystem>


class Utils
{
	public:
		static std::string readFile(const std::filesystem::path &relative_file_path);
};
