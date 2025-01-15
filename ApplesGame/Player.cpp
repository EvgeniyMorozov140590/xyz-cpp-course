#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		player.sprite.setTexture(game.playerTexture);

		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);

		sf::FloatRect spriteRect = player.sprite.getLocalBounds();
		player.sprite.setTextureRect(sf::IntRect(0, 0, (int)spriteRect.width, (int)spriteRect.height));
		player.sprite.setRotation(0);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);

		window.draw(player.sprite);
	}

	void MovePlayer(Player& player, float deltaTime)
	{
		sf::FloatRect spriteRect = player.sprite.getLocalBounds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.direction = PlayerDirection::Down;
		}

		switch (player.direction)
		{
			case PlayerDirection::Right:
			{
				player.position.x += player.speed * deltaTime;

				player.sprite.setTextureRect(sf::IntRect(0, 0, (int)spriteRect.width, (int)spriteRect.height));
				player.sprite.setRotation(0);

				break;
			}
			case PlayerDirection::Up:
			{
				player.position.y -= player.speed * deltaTime;

				player.sprite.setTextureRect(sf::IntRect(0, 0, (int)spriteRect.width, (int)spriteRect.height));
				player.sprite.setRotation(-90);

				break;
			}
			case PlayerDirection::Left:
			{
				player.position.x -= player.speed * deltaTime;

				player.sprite.setTextureRect(sf::IntRect((int)spriteRect.width, 0, (int)-spriteRect.width, (int)spriteRect.height));
				player.sprite.setRotation(0);

				break;
			}
			case PlayerDirection::Down:
			{
				player.position.y += player.speed * deltaTime;

				player.sprite.setTextureRect(sf::IntRect(0, 0, (int)spriteRect.width, (int)spriteRect.height));
				player.sprite.setRotation(90);

				break;
			}
		}
	}
}

