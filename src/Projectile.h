#pragma once
#include "Vector2.h"
#include "IEntity.h"
#include "IRenderable.h"

class Projectile : public IEntity, public IRenderable
{
private:
	int damage = 10;
	float speed = 800.0f;
	Vector2 direction = {0, 0};
	float rotation = 0.0f;
	Vector2 position = { 0, 0 };
	std::string type = "projectile";
	Vector2 size = { 5, 7 };
	float lifeTime = 2.0f;
	float age = 0.0f;
	bool isAlive = true;
public:
	Projectile(Vector2& pos, Vector2& dir, float rot) : position(pos), direction(dir), rotation(rot) {}

	void update(float deltaTime) override;
	RenderData getRenderData() const override;
	bool isAllive() override { return isAlive; };
	void onCollision(ICollidable* other) override;


	Vector2 getPosition() const override { return position; }
	float getRotation() const override { return rotation; }
	Vector2 getSize() const override { return size; }
	int getDamage() const { return damage; }
};

