#include "BotTank.h"
#include "EventType.h"
#include "EntityManager.h"
#include <ctime>

//void BotTank::publishEvent(const EventType& event)
//{
//    EventManager& eventManager = getEventManager();
//    eventManager.notify(event);
//}

void BotTank::update(float deltaTime)
{
    Tank::update(deltaTime);
    if (!targetPlayer || !map) {
        return;
    }

    checkVision(deltaTime);

    if (seesPlayer) {
        updateChase(deltaTime);
    }
    else {
        updatePatrol(deltaTime);
    }
}

bool BotTank::isPathBlocked()
{
    Vector2 botPos = getPosition();
    Vector2 playerPos = targetPlayer->getPosition();

    for (auto& obs : *obstacles) {
        Obstacle* obstacle = dynamic_cast<Obstacle*>(obs.get());
        if (!obstacle) {
            continue;
        }

        Vector2 oPos = obstacle->getPosition();
        Vector2 oSize = obstacle->getSize();

        float left = oPos.x - oSize.x / 2;
        float right = oPos.x + oSize.x / 2;
        float top = oPos.y - oSize.y / 2;
        float bottom = oPos.y + oSize.y / 2;

        Vector2 p1(left, top);
        Vector2 p2(right, top);
        Vector2 p3(right, bottom);
        Vector2 p4(left, bottom);

        if (lineIntersects(botPos, playerPos, p1, p2) ||
            lineIntersects(botPos, playerPos, p2, p3) ||
            lineIntersects(botPos, playerPos, p3, p4) ||
            lineIntersects(botPos, playerPos, p4, p1)){
            return true;
        }
    }

    return false;
}

bool BotTank::lineIntersects(Vector2& a1, Vector2& a2, Vector2& b1, Vector2& b2)
{
    float d = (a2.x - a1.x) * (b2.y - b1.y) - (a2.y - a1.y) * (b2.x - b1.x);
    if (d == 0) {
        return false;
    }

    float u = ((b1.x - a1.x) * (b2.y - b1.y) - (b1.y - a1.y) * (b2.x - b1.x)) / d;
    float v = ((b1.x - a1.x) * (a2.y - a1.y) - (b1.y - a1.y) * (a2.x - a1.x)) / d;

    return (u >= 0 && u <= 1 && v >= 0 && v <= 1);
}

void BotTank::checkVision(float deltaTime)
{
    const float VISION_RANGE = 300.0f;    
    const float MEMORY_DURATION = 3.0f;

    Vector2 botPos = getPosition();
    Vector2 playerPos = targetPlayer->getPosition();

    Vector2 toPlayer = playerPos - botPos;
    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    bool blocked = isPathBlocked();

    if (!blocked && dist < VISION_RANGE) {
        seesPlayer = true;
        loseTimer = 0.0f;
    }
    else if (blocked && seesPlayer) {
        loseTimer += deltaTime;
        if (loseTimer > MEMORY_DURATION) {
            seesPlayer = false;
            loseTimer = 0.0f;
        }
    }
}

void BotTank::updateChase(float deltaTime)
{
    const float CHASE_RANGE = 200.0f;        
    const float RETREAT_RANGE = 120.0f;      
    const float FORWARD_SPEED_FACTOR = 0.8f; 
    const float BACKWARD_SPEED_FACTOR = 0.6f;
    const float SPRITE_ROTATION_OFFSET = 90.0f;
    const float PI = 3.1415926f;

    Vector2 botPos = getPosition();
    Vector2 playerPos = targetPlayer->getPosition();
    Vector2 toPlayer = playerPos - botPos;

    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    Vector2 dir = { toPlayer.x, toPlayer.y};
    dir = dir.normalized();
    float angle = atan2(dir.y, dir.x) * 180 / PI + SPRITE_ROTATION_OFFSET;
    setRotation(angle);
    setDirection(dir);

    if (dist > 200) {
        setPosition(botPos + dir * getSpeed() * deltaTime * FORWARD_SPEED_FACTOR);
    }
    else if (dist < RETREAT_RANGE) {
        setPosition(botPos - dir * getSpeed() * deltaTime * BACKWARD_SPEED_FACTOR);
    }
    else if (dist < CHASE_RANGE) {
        shoot();
    }
}

void BotTank::updatePatrol(float deltaTime)
{
    const float PI = 3.1415926f;
    const float TURN_INTERVAL = 2.0f;    
    const int FULL_ROTATION = 360;      
    const float SPEED_FACTOR = 0.5f;  
    const float SPRITE_ROTATION_OFFSET = 90.0f;

    randTimer += deltaTime;

    if (randTimer > TURN_INTERVAL) {
        randTimer = 0;
        float angle = (std::rand() % FULL_ROTATION) * PI / 180.0f;
        randDir = { std::cos(angle), std::sin(angle) };
    }

    setDirection(randDir);
    setPosition(getPosition() + randDir * getSpeed() * deltaTime * SPEED_FACTOR);
    setRotation(atan2(randDir.y, randDir.x) * 180 / PI + SPRITE_ROTATION_OFFSET);
}

void BotTank::findPlayer()
{
    EntityManager& entityManager = getEntityManager();
    std::vector<std::unique_ptr<IEntity>>& entities = entityManager.getEntities();
    for (auto& entity : entities) {
        if (PlayerTank* playerTank = dynamic_cast<PlayerTank*>(entity.get())) {
            targetPlayer = playerTank;
            break;
        }
    }
}

void BotTank::setMap(Map* m)
{
    map = m;
    obstacles = &map->getObstacles();
}


RenderData BotTank::getRenderData() const
{
    RenderData renderData;
    renderData.position = getPosition();
    renderData.size = getSize();
    renderData.type = type;
    renderData.rotation = getRotation();
    return renderData;
}

