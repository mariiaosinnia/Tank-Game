#pragma once
#include <memory>
#include "Vector2.h"
#include "IEntityFactory.h"
#include "EntityManager.h"
#include "EventManager.h"

enum TankType {
	PLAYER_TANK,
	BOT_TANK,
	UNKNOWN_TANK
};
class TankFactory : public IEntityFactory
{
private:
	EntityManager& entityManager;
	EventManager& eventManager;
	std::unique_ptr<IEntity> create(const std::string& type, const Vector2& position) override;
	TankType parseType(const std::string& type);
public:
	TankFactory(EntityManager& entityM, EventManager& eventM) : entityManager(entityM), eventManager(eventM){}
};

