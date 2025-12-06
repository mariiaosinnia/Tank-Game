#include "InteractiveObjectFactory.h"
#include "Mine.h"
#include "HealthPack.h"
#include <iostream>

std::unique_ptr<IEntity> InteractiveObjectFactory::create(const std::string& type, const Vector2 & position)
{
	InteractiveObjectType objectType = parseType(type);
	if (objectType == MINE) {
		return std::make_unique<Mine>(position);
	}
	else if (objectType == HEALTH_PACK) {
		return std::make_unique<HealthPack>(position);
	}
	else {
		std::cout << "Unknown interactive object type" << std::endl;
		return nullptr;
	}
}

InteractiveObjectType InteractiveObjectFactory::parseType(const std::string& type)
{
	if (type == "mine") {
		return MINE;
	}
	else if (type == "healthPack") {
		return HEALTH_PACK;
	}
	else {
		return UNKNOWN_OBJECT;
	}
}
