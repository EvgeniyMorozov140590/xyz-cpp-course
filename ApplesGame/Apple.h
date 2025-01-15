#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Apple
	{
		Position2D position;
		bool isVisible = true;

		sf::Sprite sprite;
	};

	struct Game;

	void InitApple(Apple& apple, const Game& game, bool visible);

	void DrawApple(Apple& apple, sf::RenderWindow& window);

	void ToggleAppleVisible(Apple& apple);
}
