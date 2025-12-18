#pragma once

#include <filesystem>


class Utils
{
	public:
		static std::string read_file(const std::filesystem::path &relative_file_path);
};
