#include "game.hpp"

#include <SFML/Graphics.hpp>

auto main() -> int
{
	GameSpecification specification({ 1280, 720, "title" });

	Game game(specification);
	game.Run();
}
