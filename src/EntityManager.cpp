#include "EntityManager.h"

void EntityManager::addEntity(std::unique_ptr<IEntity> entity)
{
	newEntities.push_back(std::move(entity));
}

std::vector<std::unique_ptr<IEntity>>& EntityManager::getEntities()
{
	return entities;
}

std::vector<BotTank*> EntityManager::getBotTanks()
{
	std::vector<BotTank*> bots;
	for (auto& entity : entities) {
		if (BotTank* bot = dynamic_cast<BotTank*>(entity.get())) {
			bots.push_back(bot);
		}
	}
	return bots;
}

void EntityManager::clear()
{
	entities.clear();
	newEntities.clear();
}

void EntityManager::updateAll(float deltaTime)
{
	if (!newEntities.empty()) {
		for (auto& e : newEntities)
			entities.push_back(std::move(e));
		newEntities.clear();
	}

	for (auto& entity : entities) {
		entity->update(deltaTime);
	}

	entities.erase(std::remove_if(entities.begin(), entities.end(), [](const std::unique_ptr<IEntity>& e) {
		return !e->isAllive();
		}), entities.end());
}

PlayerTank* EntityManager::getPlayer()
{
	for (auto& entity : entities) {
		if (PlayerTank* player = dynamic_cast<PlayerTank*>(entity.get())) {
			return player;
		}
	}
	return nullptr;
}

std::vector<BotTank*> EntityManager::getBots()
{
	std::vector<BotTank*> bots;
	for (auto& entity : entities) {
		if (BotTank* bot = dynamic_cast<BotTank*>(entity.get())) {
			bots.push_back(bot);
		}
	}
	return bots;
}

