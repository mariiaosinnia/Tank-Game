#pragma once
#include <vector>
#include <memory>
#include "IEntity.h"
#include "PlayerTank.h"
#include "BotTank.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<IEntity>> entities;
	std::vector<std::unique_ptr<IEntity>> newEntities;
public:
	EntityManager(){}
	void addEntity(std::unique_ptr<IEntity> entity);
	std::vector<std::unique_ptr<IEntity>>& getEntities();
	std::vector<BotTank*> getBotTanks();
	void clear();
	void updateAll(float deltaTime);
	PlayerTank* getPlayer();
	std::vector<BotTank*> getBots();
};

