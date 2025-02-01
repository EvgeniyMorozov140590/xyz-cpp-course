#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct UserInterface
	{
		sf::Text scoreText;
		sf::Text hintText;
		sf::Text gameOverText;
		sf::Text gameModeText;
		std::vector<sf::Text> recordsText;
		sf::Text exitDialogText;
	};

	struct Game;

	void InitUserInterface(UserInterface& userInterface, const Game& game);

	void UpdateUserInterface(UserInterface& userInterface, const Game& game);

	void DrawUserInterface(const Game& game, sf::RenderWindow& window);
}
