#pragma once
#include <string>

namespace ApplesGame
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f;
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 10.f;

	const int NUM_APPLES = 3;
	const int MIN_APPLES = 2;
	const float APPLE_SIZE = 20.f;

	const float ROCK_SIZE = 30.f;
	const int NUM_ROCKS = 5;

	const std::string DEFAULT_MODE = "Default;\n";
	const std::string INFINITY_APPLES_MODE = "Infinity apples;\n";
	const std::string ACCELERATION_AFTER_EATING_MODE = "Acceleration after eating;\n";
	const std::string PLAYER_NAME = "Player";

	const std::string RESOURCES_PATH = "Resources/";
}
