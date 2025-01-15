// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)
#include "Game.h"

int main()
{	
	using namespace ApplesGame;

	int seed = (int)time(nullptr);

	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game");

	Game game;

	InitGame(game);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::sleep(sf::milliseconds(16));

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				RestartGame(game, gameClock);
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
			{
				ToggleGameSettings(game, GameSettings::InfiniteApples);
			}
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
			{
				ToggleGameSettings(game, GameSettings::Acceleration);
			}
		}

		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		UpdateGame(game, deltaTime, currentTime);

		window.clear();

		DrawGame(game, window);

		window.display();
	}

	return 0;
}
