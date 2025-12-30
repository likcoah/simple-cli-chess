#include "game_loop.hpp"
#include "source_dir.hpp"

#include <ios>

int main(int argc, char *argv[])
{
	SourceDir::setSourceDir(argv[0]);

	std::ios::sync_with_stdio(false);

	GameLoop loop;
	loop.loop();

	return 0;
}
