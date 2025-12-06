#pragma once
#include "IEntity.h"
#include "InteractiveObject.h"
#include "Vector2.h"

class Mine : public InteractiveObject
{
private:
	int damage = 0;
	std::string type = "mine";
public:
	Mine(const Vector2& p, int d = 20) : InteractiveObject(p), damage(d){}

	void interact(Tank* tank) override;
	RenderData getRenderData() const override;
};

