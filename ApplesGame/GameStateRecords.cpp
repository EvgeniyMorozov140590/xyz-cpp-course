#include "GameStateRecords.h"
#include <assert.h>
#include "Game.h"

namespace ApplesGame
{
	void InitGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.recordsTableText.setFillColor(sf::Color::Green);
		data.recordsTableText.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void ShutdownGameStateRecords(GameStateRecordsData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateRecordsWindowEvent(GameStateRecordsData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateRecords(GameStateRecordsData& data, Game& game, float timeDelta)
	{
		data.recordsTableText.setString("Records:");
		for (const RecordsTableItem& item : game.recordsTable)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
		}
		data.recordsTableText.setOrigin(GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void DrawGameStateRecords(GameStateRecordsData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);
	}
}
