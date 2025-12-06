#include "InteractiveObject.h"
#include "Tank.h"

void InteractiveObject::update(float deltaTime)
{
	age += deltaTime;
	if (age >= lifeTime) {
		isAlive = false;
	}
}

void InteractiveObject::onCollision(ICollidable* other)
{
	if (Tank* tank = dynamic_cast<Tank*>(other)) {
		interact(tank);
		isAlive = false;
	}
}





