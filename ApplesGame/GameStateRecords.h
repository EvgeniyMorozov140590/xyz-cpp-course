#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct Game;

	struct GameStateRecordsData
	{
		sf::Font font;
		sf::Text recordsTableText;
	};

	void InitGameStateRecords(GameStateRecordsData& data, Game& game);
	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game);
	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event);
	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta);
	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window);
}
