#include "game_loop.hpp"
#include "source_dir.hpp"

int main(int argc, char *argv[])
{
	SourceDir::setSourceDir(argv[0]);
	GameLoop loop;
	loop.loop();
	return 0;
}
