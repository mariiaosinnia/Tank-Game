#pragma once
#include "Tank.h"
#include "RenderData.h"
#include "IEventPublisher.h"
#include "IEventListener.h"
class PlayerTank : public Tank, public IEventPublisher, public IEventListener
{
private:
	std::string type = "playerTank";
	bool movingForward = false;
	bool movingBackward = false;
	bool turningRight = false;
	bool turningLeft = false;
public:
	PlayerTank(EntityManager& entityM, EventManager& eventM, const Vector2& position) : Tank(entityM, eventM, position) {}
	RenderData getRenderData() const override;
	void publishEvent(const EventType& event) override;
	void onEvent(const EventType& event) override;
	void update(float deltaTime) override;
};

