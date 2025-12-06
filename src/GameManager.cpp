#include "GameManager.h"
#include "IEntityFactory.h"
#include "EventType.h"
#include "Tank.h"
#include "Vector2.h"
#include "BotTank.h"
#include "Mine.h"
#include "HealthPack.h"
#include <random>

void GameManager::init() {
	Vector2 playerPosition = { 70, 410 };
	std::string type = "player";
	std::unique_ptr<IEntity> playerTank = tankFactory.create(type, playerPosition);
	PlayerTank* playerPtr = dynamic_cast<PlayerTank*>(playerTank.get());
	eventManager.subscribe(EventType::MovingForward, dynamic_cast<IEventListener*>(playerTank.get()));
	eventManager.subscribe(EventType::MovingBackward, dynamic_cast<IEventListener*>(playerTank.get()));
	eventManager.subscribe(EventType::TurnLeft, dynamic_cast<IEventListener*>(playerTank.get()));
	eventManager.subscribe(EventType::TurnRight, dynamic_cast<IEventListener*>(playerTank.get()));
    eventManager.subscribe(EventType::StopForward, dynamic_cast<IEventListener*>(playerTank.get()));
    eventManager.subscribe(EventType::StopBackward, dynamic_cast<IEventListener*>(playerTank.get()));
    eventManager.subscribe(EventType::StopTurnLeft, dynamic_cast<IEventListener*>(playerTank.get()));
    eventManager.subscribe(EventType::StopTurnRight, dynamic_cast<IEventListener*>(playerTank.get()));
    eventManager.subscribe(EventType::Shoot, dynamic_cast<IEventListener*>(playerTank.get()));
	entityManager.addEntity(std::move(playerTank));

    const Vector2 botPositions[] = {
        {890, 610}, {890, 310}
    };

    for (int i = 0; i < botCount; ++i) {
        std::string botType = "bot";
        std::unique_ptr<IEntity> botTank = tankFactory.create(botType, botPositions[i]);
        BotTank* botPtr = dynamic_cast<BotTank*>(botTank.get());
        if (botPtr) {
            botPtr->setTarget(playerPtr);
            botPtr->setMap(map);
        }
        entityManager.addEntity(std::move(botTank));
    }

	eventManager.subscribe(EventType::GameOver, dynamic_cast<IEventListener*>(this));
    eventManager.subscribe(EventType::Victory, dynamic_cast<IEventListener*>(this));

    botsWereSpawned = true;
}
void GameManager::update(float deltaTime)
{
    if (gameState != GameState::Running) {
        return;
    }

    timeSinceLastMine += deltaTime;
    timeSinceLastHealthPack += deltaTime;

    if (timeSinceLastMine >= mineSpawnInterval) {
        Vector2 pos = getRandomPosition();
        entityManager.addEntity(std::make_unique<Mine>(pos));
        timeSinceLastMine = 0.0f;
    }

    if (timeSinceLastHealthPack >= healthPackSpawnInterval) {
        Vector2 pos = getRandomPosition();
        entityManager.addEntity(std::make_unique<HealthPack>(pos));
        timeSinceLastHealthPack = 0.0f;
    }

    if (areAllBotsDead()) {
        eventManager.notify(EventType::Victory);
    }
}

void GameManager::reset()
{
    eventManager.unsubscribeAll();
    entityManager.clear();
    botsWereSpawned = false;

    init();
    gameState = GameState::Running;
    timeSinceLastHealthPack = 0.0f;
    timeSinceLastMine = 0.0f;
}

Vector2 GameManager::getRandomPosition()
{
    const float MAP_WIDTH = 960.0f;
    const float MAP_HEIGHT = 720.0f;
    const float MARGIN_TOP = 250.0f;
    const float MARGIN_BOTTOM = 170.0f;
    const float MARGIN_SIDES = 230.0f;
    std::uniform_real_distribution<float> distX(MARGIN_SIDES, MAP_WIDTH - MARGIN_SIDES);
    std::uniform_real_distribution<float> distY(MARGIN_TOP, MAP_HEIGHT - MARGIN_BOTTOM);
    return Vector2{ distX(rng), distY(rng) };
}

void GameManager::onEvent(const EventType& event)
{
    if(event == EventType::GameOver) {
        gameState = GameState::GameOver;
        shouldReset = true;
    }
    else if (event == EventType::Victory) {
        gameState = GameState::Victory;
        shouldReset = true;
    }
}

bool GameManager::areAllBotsDead() const {
    std::vector<BotTank*> bots = entityManager.getBotTanks();

    if (!botsWereSpawned) {
        return false;
    }
    if (bots.empty()) {
        return true;
    }
    return false;
}


