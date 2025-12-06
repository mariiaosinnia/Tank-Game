#pragma once
#include "Vector2.h"
#include "IRenderable.h"
#include "ICollidable.h"
class Obstacle : public IRenderable, public ICollidable
{
private:
	Vector2 position = { 0, 0 };
	Vector2 size = { 1, 1 };
	std::string type = "obstacle";
	float rotation = 0.0f;
public:
	Obstacle(const Vector2& p, const Vector2& s) : position(p), size(s) {}
	void onCollision(ICollidable* other) override;

	RenderData getRenderData() const override;
	Vector2 getPosition() const override { return position; }
	float getRotation() const override { return rotation; }
	Vector2 getSize() const override { return size; }
};

