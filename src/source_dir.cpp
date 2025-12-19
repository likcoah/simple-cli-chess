#include "source_dir.hpp"

#include <filesystem>
#include <string>


static std::filesystem::path source_dir;


void SourceDir::setSourceDir(const char *binary_file_path)
{
	source_dir = std::filesystem::weakly_canonical(std::filesystem::absolute(binary_file_path).parent_path());
}

std::string SourceDir::getSourceDir()
{
	return source_dir.string();
}
