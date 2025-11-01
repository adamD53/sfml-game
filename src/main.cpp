#include "game.h"

#include <SFML/Graphics.hpp>

int main()
{
	GameSpecification specification({ 1280, 720, "title" });

	Game game(specification);
	game.Run();
}