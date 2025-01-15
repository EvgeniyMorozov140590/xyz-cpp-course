#include "Rock.h"
#include "Game.h"

namespace ApplesGame 
{
	void InitRock(Rock& rock, const Game& game)
	{
		rock.sprite.setTexture(game.rockTexture);
		rock.sprite.setPosition(rock.position.x, rock.position.y);

		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		window.draw(rock.sprite);
	}
}
