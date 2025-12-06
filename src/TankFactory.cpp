#include <iostream>
#include "TankFactory.h"
#include "PlayerTank.h"
#include "BotTank.h"

std::unique_ptr<IEntity> TankFactory::create(const std::string& type, const Vector2& position)
{
    TankType tankType = parseType(type);
    if (tankType == PLAYER_TANK) {
        return std::make_unique<PlayerTank>(entityManager, eventManager, position);
    }
    else if (tankType == BOT_TANK) {
        return std::make_unique<BotTank>(entityManager, eventManager, position);
    }
    else {
        std::cout << "Unknown tank type" << std::endl;
        return nullptr;
    }
}

TankType TankFactory::parseType(const std::string& type)
{
    if (type == "player") {
        return PLAYER_TANK;
    }
    else if (type == "bot") {
        return BOT_TANK;
    }
    else {
        return UNKNOWN_TANK;
    }
}
