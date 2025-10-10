#include "game.h"

#include <SFML/Graphics.hpp>

//std::tuple<sf::Vector2> getSize()
//{
//
//}

int main()
{
	GameSpecification specification({ 1280, 720, "title" });

	Game game(specification);
	game.Run();
}