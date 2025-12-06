#pragma once
#include "Vector2.h"
#include "ICollidable.h"

class IEntity : public ICollidable{
public:
	virtual void update(float deltaTime) = 0;
	virtual bool isAllive() = 0; 
	virtual ~IEntity() = default;
};
