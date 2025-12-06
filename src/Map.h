#pragma once
#include <vector>
#include "Obstacle.h"
#include <memory>
class Map
{
private:
	std::vector<std::unique_ptr<ICollidable>> obstacles;
public:
	Map() {
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 10, 430 }, Vector2{ 20, 660 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 950, 430 }, Vector2{ 20, 660 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 480, 110 }, Vector2{ 920, 20 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 480, 710 }, Vector2{ 920, 20 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 200, 400 }, Vector2{ 20, 200 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 760, 400 }, Vector2{ 20, 200 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 480, 220 }, Vector2{ 300, 20 }
		));
		obstacles.push_back(std::make_unique<Obstacle>(
			Vector2{ 480, 580 }, Vector2{ 300, 20 }
		));
	}
	const std::vector<std::unique_ptr<ICollidable>>& getObstacles() const {
		return obstacles;
	}
};

