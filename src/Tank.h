#pragma once
#include "IEntity.h"
#include "IRenderable.h"
#include "Vector2.h"
#include "EventManager.h"
#include "ICollidable.h"
class EntityManager;

class Tank : public IEntity, public IRenderable
{
private:
	int health = 100;
	int maxHealth = 100;
	bool isAlive = true;
	EntityManager& entityManager;
	EventManager& eventManager;
	Vector2 position = {0, 0};
	Vector2 previousPosition;
	Vector2 direction = {0, 0};
	Vector2 size = { 30, 40 };
	float speed = 150.0f;
	float rotation = 0.0f;
	float rotationSpeed = 75.0f;

	float fireCooldown = 0.3f;
	float timeSinceLastShot = fireCooldown;
public:
	Tank(EntityManager& entityM, EventManager& eventM, const Vector2& p) : entityManager(entityM), eventManager(eventM), position(p) {}

	virtual RenderData getRenderData() const = 0;
	virtual void update(float deltaTime) = 0;
	void shoot();
	void takeDamage(int damage);
	void heal(int healBonus);
	void onCollision(ICollidable* other) override;

	Vector2 getPosition() const override { return position; }
	void setPosition(const Vector2& pos) { position = pos; }

	Vector2 getDirection() const { return direction; }
	void setDirection(const Vector2& dir) { direction = dir;}

	Vector2 getSize() const override { return size; }

	float getSpeed() const { return speed; }

	float getRotation() const override { return rotation; }
	void setRotation(float r) { rotation = r; }

	float getRotationSpeed() const { return rotationSpeed; }
	void setRotationSpeed(float rSpeed) { rotation = rSpeed; }

	EventManager& getEventManager() { return eventManager; }
	EntityManager& getEntityManager() { return entityManager; }

	int getMaxHealth() const { return maxHealth; }
	int getHealth() const { return health; }

	bool isAllive() override { return isAlive; };
};

