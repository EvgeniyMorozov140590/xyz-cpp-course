#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Apple.h"
#include "GameSettings.h"

namespace ApplesGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	struct RecordsTableItem
	{
		std::string name;
		int score = 0;
	};

	bool operator<(const RecordsTableItem& lhs, const RecordsTableItem& rhs);

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTableItem recordsTable[MAX_RECORDS_TABLE_SIZE];
	};

	
	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, float timeDelta);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	void PopGameState(Game& game);

	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float timeDelta);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}
