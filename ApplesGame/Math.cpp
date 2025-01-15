#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;

		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;

		return result;
	}

	Position2D GetRandomPositionWithRange(float minX, float minY, float maxX, float maxY)
	{
		Position2D result;

		result.x = minX + rand() % (int)maxX;
		result.y = minY + rand() % (int)maxY;

		return result;
	}

	int GetRandomNumberWithRange(int min, int max)
	{
		return static_cast<int>(min + rand() % max);
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Position.x - rect2Position.x);
		float dy = (float)fabs(rect1Position.y - rect2Position.y);

		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	bool IsCiclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		float squaredistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x) +
			(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		float squareRadius = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);

		return squaredistance <= squareRadius;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };

		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();

		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	Position2D GetTextOrigin(sf::Text& text)
	{
		const sf::FloatRect textRect = text.getLocalBounds();

		const Position2D origin = { textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f };

		return origin;
	}
}


