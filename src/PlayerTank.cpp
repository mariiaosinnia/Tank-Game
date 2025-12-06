#include "PlayerTank.h"
#include "EventType.h"
RenderData PlayerTank::getRenderData() const
{
    RenderData renderData;
    renderData.position = getPosition();
    renderData.size = getSize();
    renderData.type = type;
    renderData.rotation = getRotation();
    return renderData;
}

void PlayerTank::onEvent(const EventType & event)
{
    switch (event) {
        case EventType::MovingForward:  
            movingForward = true; 
            break;
        case EventType::StopForward:    
            movingForward = false; 
            break;
        case EventType::MovingBackward: 
            movingBackward = true; 
            break;
        case EventType::StopBackward:   
            movingBackward = false; 
            break;
        case EventType::TurnLeft:       
            turningLeft = true; 
            break;
        case EventType::StopTurnLeft:   
            turningLeft = false; 
            break;
        case EventType::TurnRight:      
            turningRight = true; 
            break;
        case EventType::StopTurnRight:  
            turningRight = false; 
            break;
        case EventType::Shoot:          
            shoot(); 
            break;
        default: 
            break;
    }
}

void PlayerTank::publishEvent(const EventType& event)
{
    EventManager& eventManager = getEventManager();
    eventManager.notify(event);
}   

void PlayerTank::update(float deltaTime)
{
    Tank::update(deltaTime);
    if (!isAllive()) {
        EventType event = EventType::GameOver;
        publishEvent(event);
        IEventListener& playerTank = *dynamic_cast<IEventListener*>(this);
        getEventManager().unsubscribe(playerTank);
    }
    const float PI = 3.1415926f;

    float rotation = getRotation();
    float rotationSpeed = getRotationSpeed();

    if (turningLeft) {
        rotation -= rotationSpeed * deltaTime;
    }
    if (turningRight) {
        rotation += rotationSpeed * deltaTime;
    }
    setRotation(rotation);

    float radRotation = rotation * PI / 180;

    float speed = getSpeed();
    Vector2 position = getPosition();

    Vector2 direction = { std::sin(radRotation), -std::cos(radRotation) };
    setDirection(direction);
    if (movingForward) {
        position += direction * speed * deltaTime;
    }
    if (movingBackward) {
        position -= direction * speed * deltaTime;
    }

    setPosition(position);
}


