#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include <iostream>

Level::Level(const sf::Vector3i& size, int new_data[], const sf::Vector2f& spawn):
	player(spawn), view(sf::FloatRect(0, 0, 1000, 600)), grid(size, new_data)
{

}

void Level::update()
{
	player.update();

	sf::Vector2f player_pos = player.getPos();
	sf::Vector2f player_speed = player.getSpeed();

	if (grid.getTileByPos(grid.convertCoord(player_pos.x), grid.convertCoord(player_pos.y) + 1) == 1 && player_speed.y > 0)
	{
		player_pos.y = grid.unconvertCoord(grid.convertCoord(player_pos.y));
		player_speed.y = 0;
		player.airbone = false;
	}

	if (grid.getTileByPos(grid.convertCoord(player_pos.x), grid.convertCoord(player_pos.y)) == 1 && player_speed.y < 0)
	{
		player_pos.y = grid.unconvertCoord(grid.convertCoord(player_pos.y) + 1);
		player_speed.y = 0;
	}

	if (grid.getTileByPos(grid.convertCoord(player_pos.x), grid.convertCoord(player_pos.y)) == 1 && player_speed.x > 0)
	{
		player_pos.x = grid.unconvertCoord(grid.convertCoord(player_pos.x));
		player_speed.x = 0;
	}

	if (grid.getTileByPos(grid.convertCoord(player_pos.x), grid.convertCoord(player_pos.y)) == 1 && player_speed.x < 0)
	{
		player_pos.x = grid.unconvertCoord(grid.convertCoord(player_pos.x) + 1);
		player_speed.x = 0;
	}

	player.setPos(player_pos);
	player.setSpeed(player_speed);

	if (grid.convertCoord(player.getPos().y) > grid.getSize().y * 2)
	{
		player.setPos(sf::Vector2f(0, 0));
		player.setSpeed(sf::Vector2f(0, 0));
	}
}