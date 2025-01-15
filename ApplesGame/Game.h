#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UserInterface.h"

namespace ApplesGame
{

	enum class GameSettings
	{
		Default = 0 << 0,
		InfiniteApples = 1 << 0,
		Acceleration = 1 << 1,
	};

	enum class GameState
	{
		None = 0,
		Playing,
		GameOver
	};

	struct Game
	{
		Player player;
		Apple apples[NUM_APPLES];
		Rock rocks[NUM_ROCKS];
		std::unordered_map<std::string, int> recordsTable;

		std::vector<GameState> gameStateStack;

		float startDelay = 0.f;
		int numEatenApples = 0;
		int randomApplesCount = 0;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		sf::SoundBuffer deathSoundBuffer;
		sf::Sound deathSound;

		sf::SoundBuffer eatingSoundBuffer;
		sf::Sound eatingSound;

		UserInterface userInterface;
		sf::Font font;

		GameSettings gameSettings = GameSettings::Default;
	};

	void InitGame(Game& game);

	void UpdateGame(Game& game, float deltaTime, float currentTime);

	void RestartGame(Game& game, sf::Clock& gameClock);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void ToggleGameSettings(Game& game, GameSettings gameSettings);

	bool IsGameSettingsOn(const Game& game, GameSettings gameSettings);
}