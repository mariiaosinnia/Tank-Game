#pragma once
#include "InteractiveObject.h"
#include "Vector2.h"

class HealthPack : public InteractiveObject
{
private:
	int healthBonus = 10;
	std::string type = "healthPack";
public:
	HealthPack(const Vector2& p, int bonus = 10) : InteractiveObject(p), healthBonus(bonus){}

	void interact(Tank* tank) override;
	RenderData getRenderData() const override;
};

