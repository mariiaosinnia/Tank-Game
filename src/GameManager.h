#pragma once
#include "EventManager.h"
#include "EntityManager.h"
#include "IEntityFactory.h"
#include "CollisionManager.h"
#include <random>

enum class GameState {
	Running,
	GameOver,
	Victory
};

class GameManager : public IEventListener
{
private:
	EventManager& eventManager;
	EntityManager& entityManager;

	IEntityFactory& tankFactory;
	IEntityFactory& interactiveObjectFactory;

	Map* map;

	GameState gameState = GameState::Running;
	float timeSinceLastMine = 0.0f;
	float timeSinceLastHealthPack = 0.0f;
	float mineSpawnInterval = 5.0f;
	float healthPackSpawnInterval = 7.0f;
	int botCount = 2;
	std::mt19937 rng;

	bool shouldReset = false;
	bool botsWereSpawned = false;

public:
	GameManager(EventManager& eventM, EntityManager& entityM, IEntityFactory& tankF, 
		IEntityFactory& interactiveObjF, Map* m) : eventManager(eventM), entityManager(entityM), tankFactory(tankF), 
		interactiveObjectFactory(interactiveObjF), map(m){
	}
	void init();
	void update(float deltaTime);
	void reset();
	bool areAllBotsDead() const;

	Vector2 getRandomPosition();
	GameState getGameState() const { return gameState; }
	bool getShouldReset() const { return shouldReset; }
	void setShouldReset(bool shouldR) { shouldReset = shouldR; }

	void onEvent(const EventType& event) override;
};

