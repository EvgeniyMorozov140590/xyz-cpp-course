#include "Game.h"
#include <cassert>
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.deathSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.eatingSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Black.ttf"));

		InitUserInterface(game.userInterface, game);

		game.recordsTable =
		{
			{"Bravo", GetRandomNumberWithRange(0, NUM_APPLES)},
			{"Delta", GetRandomNumberWithRange(0, NUM_APPLES)},
			{"Alfa", GetRandomNumberWithRange(0, NUM_APPLES)},
			{"Fast", GetRandomNumberWithRange(0, NUM_APPLES)},
			{"Shadow", GetRandomNumberWithRange(0, NUM_APPLES)},
			{PLAYER_NAME, 0},
		};

		game.deathSound.setBuffer(game.deathSoundBuffer);
		game.eatingSound.setBuffer(game.eatingSoundBuffer);

		game.randomApplesCount = GetRandomNumberWithRange(MIN_APPLES, NUM_APPLES);

		InitPlayer(game.player, game);

		for (int i = 0; i < NUM_APPLES; i++)
		{
			bool isAppleVisible = i < game.randomApplesCount;

			InitApple(game.apples[i], game, isAppleVisible);
		}

		for (int i = 0; i < NUM_ROCKS; i++)
		{
			game.rocks[i].position = GetRandomPositionWithRange(0.f, 0.f, SCREEN_WIDTH / 2 - PLAYER_SIZE - ROCK_SIZE, SCREEN_HEIGHT - PLAYER_SIZE - ROCK_SIZE);

			if (i > NUM_ROCKS / 2) {
				game.rocks[i].position = GetRandomPositionWithRange(
					SCREEN_WIDTH / 2 + PLAYER_SIZE + ROCK_SIZE,
					0.f,
					SCREEN_WIDTH - ROCK_SIZE,
					SCREEN_HEIGHT - PLAYER_SIZE - ROCK_SIZE
				);
			}

			InitRock(game.rocks[i], game);
		}

		game.startDelay = 1.f;

		game.numEatenApples = 0;

		game.gameStateStack.push_back(GameState::Playing);

		game.gameSettings = GameSettings::Default;
	};

	void UpdateGame(Game& game, float deltaTime, float currentTime)
	{
		if (game.gameStateStack.back() == GameState::Playing && currentTime > game.startDelay)
		{
			MovePlayer(game.player, deltaTime);

			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH
				|| game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				game.deathSound.play();

				game.gameStateStack.push_back(GameState::GameOver);
			}

			for (int i = 0; i < NUM_APPLES; i++)
			{
				if (game.apples[i].isVisible && IsCiclesCollide(game.player.position, PLAYER_SIZE / 2, game.apples[i].position, APPLE_SIZE / 2))
				{
					++game.numEatenApples;

					if (IsGameSettingsOn(game, GameSettings::Acceleration))
					{
						game.player.speed += ACCELERATION;
					}

					if (IsGameSettingsOn(game, GameSettings::InfiniteApples))
					{
						game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

						game.apples[i].sprite.setPosition(game.apples[i].position.x, game.apples[i].position.y);
					}
					else 
					{
						ToggleAppleVisible(game.apples[i]);

						if (game.randomApplesCount == game.numEatenApples)
						{
							game.gameStateStack.push_back(GameState::GameOver);
						}
					}

					game.eatingSound.play();
				}
			}

			for (int i = 0; i < NUM_ROCKS; i++)
			{
				if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, game.rocks[i].position, { ROCK_SIZE, ROCK_SIZE }))
				{
					game.deathSound.play();

					game.gameStateStack.push_back(GameState::GameOver);
				}
			}

			if (game.gameStateStack.back() == GameState::GameOver)
			{
				game.recordsTable[PLAYER_NAME] = std::max(game.recordsTable[PLAYER_NAME],
					game.numEatenApples);
			}

			UpdateUserInterface(game.userInterface, game);
		}
	};

	void RestartGame(Game& game, sf::Clock& gameClock)
	{
		if (game.gameStateStack.back() == GameState::GameOver)
		{
			game.gameStateStack.clear();

			InitGame(game);

			gameClock.restart();

			UpdateUserInterface(game.userInterface, game);

			game.randomApplesCount = 0;
		}
	};

	void DrawGame(Game& game, sf::RenderWindow& window)
	{

		DrawPlayer(game.player, window);

		for (int i = 0; i < NUM_APPLES; i++)
		{
			DrawApple(game.apples[i], window);
		}

		for (int i = 0; i < NUM_ROCKS; i++)
		{
			DrawRock(game.rocks[i], window);
		}

		DrawUserInterface(game.userInterface, window);
	}

	void ToggleGameSettings(Game& game, GameSettings gameSettings)
	{
		game.gameSettings = static_cast<GameSettings>((static_cast<int>(game.gameSettings) ^ static_cast<int>(gameSettings)));
	}

	bool IsGameSettingsOn(const Game& game, GameSettings gameSettings)
	{
		return static_cast<int>(game.gameSettings) & static_cast<int>(gameSettings);
	}
}