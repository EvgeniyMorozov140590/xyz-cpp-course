#include "Game.h"
#include "Constants.h"
#include <sstream>

namespace ApplesGame
{
	void InitUserInterface(UserInterface& userInterface, const Game& game)
	{
		userInterface.scoreText.setFont(game.font);
		userInterface.scoreText.setString("score: " + std::to_string(game.numEatenApples));
		userInterface.scoreText.setCharacterSize(32);
		userInterface.scoreText.setFillColor(sf::Color::Green);
		userInterface.scoreText.setOrigin(0.5f, 0.5f);
		userInterface.scoreText.setPosition(20.f, 10.f);

		userInterface.hintText.setFont(game.font);
		userInterface.hintText.setString("up, down, left, right - move; space - restart game;\n1 - infinite apples; 2 - speed up after eating");
		userInterface.hintText.setCharacterSize(14);
		userInterface.hintText.setFillColor(sf::Color::Yellow);
		userInterface.hintText.setOrigin(0.5f, 0.5f);
		userInterface.hintText.setPosition(250.f, 25.f);
		
		userInterface.gameModeText.setFont(game.font);
		userInterface.gameModeText.setString(std::string("Mode:\n" + DEFAULT_MODE));
		userInterface.gameModeText.setCharacterSize(14);
		userInterface.gameModeText.setFillColor(sf::Color::Blue);
		userInterface.gameModeText.setOrigin(0.5f, 0.5f);
		userInterface.gameModeText.setPosition(20.f, 50.f);

		userInterface.gameOverText.setFont(game.font);
		userInterface.gameOverText.setCharacterSize(64);
		userInterface.gameOverText.setFillColor(sf::Color::Red);
		userInterface.gameOverText.setString("GAME OVER!!!");

		const Position2D gameOverOrigin = GetTextOrigin(userInterface.gameOverText);

		userInterface.gameOverText.setOrigin(gameOverOrigin.x, gameOverOrigin.y);
		userInterface.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f);

		userInterface.exitDialogText.setFont(game.font);
		userInterface.exitDialogText.setCharacterSize(24);
		userInterface.exitDialogText.setFillColor(sf::Color::Yellow);
		userInterface.exitDialogText.setString("Do you wanna exit?\n Press Enter - main menu | ESC - continue" );

		const Position2D exitDialogTextOrigin = GetTextOrigin(userInterface.exitDialogText);

		userInterface.exitDialogText.setOrigin(exitDialogTextOrigin.x, exitDialogTextOrigin.y);
		userInterface.exitDialogText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.f);

		userInterface.recordsText.clear();
	}

	void UpdateUserInterface(UserInterface& userInterface, const Game& game)
	{
		const std::string infinityApplesText = IsGameSettingsOn(game, GameSettings::InfiniteApples) ? INFINITY_APPLES_MODE : "";
		const std::string accelerationAfterEatingText = IsGameSettingsOn(game, GameSettings::Acceleration) ? ACCELERATION_AFTER_EATING_MODE : "";
		const std::string defaultText = !(IsGameSettingsOn(game, GameSettings::InfiniteApples) || IsGameSettingsOn(game, GameSettings::Acceleration)) ? DEFAULT_MODE : "";

		userInterface.scoreText.setString("score: " + std::to_string(game.numEatenApples));
		userInterface.gameModeText.setString(std::string("Mode:\n" + infinityApplesText + accelerationAfterEatingText + defaultText));

		if (game.gameStateStack.back() == GameState::GameOver) {
			std::multimap<int, std::string> sortedRecordsTable;

			for (const auto& item : game.recordsTable)
			{
				sortedRecordsTable.insert(std::make_pair(item.second, item.first));
			}

			auto it = sortedRecordsTable.rbegin();

			for (int i = 0; i < game.recordsTable.size() && it != sortedRecordsTable.rend(); ++i, ++it)
			{
				userInterface.recordsText.emplace_back();

				sf::Text& text = userInterface.recordsText.back();
				std::stringstream sstream;

				sstream << i + 1 << ". " << it->second << ": " << it->first;

				text.setString(sstream.str());
				text.setCharacterSize(24);
				text.setFont(game.font);

				const Position2D recordsOrigin = GetTextOrigin(text);

				text.setOrigin(0.5f, recordsOrigin.y);
				text.setPosition((SCREEN_WIDTH / 2.f) - 100, i * 24 + SCREEN_HEIGHT / 2.f);

				if (it->second == PLAYER_NAME)
				{
					text.setFillColor(sf::Color::Green);
				}
				else
				{
					text.setFillColor(sf::Color::Yellow);
				}
			};
		}
	}

	void DrawUserInterface(const Game& game, sf::RenderWindow& window)
	{
		window.draw(game.userInterface.scoreText);
		window.draw(game.userInterface.hintText);
		window.draw(game.userInterface.gameModeText);

		if (game.gameStateStack.back() == GameState::GameOver)
		{
			window.draw(game.userInterface.gameOverText);
		}

		if (game.gameStateStack.back() == GameState::GameOver)
		{
			for (sf::Text item : game.userInterface.recordsText)
			{
				window.draw(item);
			}
		}

		if (game.gameStateStack.back() == GameState::ExitDialog)
		{
			window.clear(sf::Color::Black);
			window.draw(game.userInterface.exitDialogText);
		}
	}
}
