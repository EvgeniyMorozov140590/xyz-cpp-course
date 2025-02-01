#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct Game;

	struct GameStateGameOverData
	{
		sf::Font font;

		float timeSinceGameOver = 0.f;

		sf::Text gameOverText;
		sf::Text hintText;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}
