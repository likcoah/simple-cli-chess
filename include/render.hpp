#pragma once

#include <filesystem>
#include <unordered_map>


// Menus render
void render(const std::filesystem::path& template_path, const std::unordered_map<char, std::string>& replace_symbols);

