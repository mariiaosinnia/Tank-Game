#pragma once

class ICollidable {
public:
	virtual void onCollision(ICollidable* other) = 0;
	virtual Vector2 getPosition() const = 0;
	virtual float getRotation() const = 0;
	virtual Vector2 getSize() const = 0;
	virtual ~ICollidable() = default;
};
