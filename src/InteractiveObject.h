#pragma once
#include "IEntity.h"
#include "Vector2.h"
#include "IRenderable.h"
class Tank;

class InteractiveObject : public IEntity, public IRenderable
{
private:
	Vector2 position{0,0};
	float rotation = 0;
	Vector2 size{25,25};
	bool isAlive = true;
	float lifeTime = 5.0f;
	float age = 0.0f;
public:
	InteractiveObject(const Vector2& p) : position(p) {}
	void update(float deltaTime) override;
	bool isAllive() override { return isAlive; };
	void onCollision(ICollidable* other) override;
	virtual void interact(Tank* tank) = 0;

	Vector2 getPosition() const override { return position; };
	float getRotation() const override { return rotation; }
	Vector2 getSize() const override { return size; };

	RenderData getRenderData() const = 0;
};

