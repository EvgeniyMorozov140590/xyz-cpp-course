#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, const Game& game, bool visible = true)
	{
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		apple.isVisible = visible;

		apple.sprite.setTexture(game.appleTexture);
		apple.sprite.setPosition(apple.position.x, apple.position.y);

		apple.sprite.setTexture(game.appleTexture);
		apple.sprite.setPosition(apple.position.x, apple.position.y);

		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isVisible) {
			window.draw(apple.sprite);
		}
	}

	void ToggleAppleVisible(Apple& apple)
	{
		apple.isVisible = !apple.isVisible;
	}
}