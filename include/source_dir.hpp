#pragma once

#include <string>


class SourceDir
{
	public:
		static void setSourceDir(const char *binary_file_path);
		static std::string getSourceDir();
};
