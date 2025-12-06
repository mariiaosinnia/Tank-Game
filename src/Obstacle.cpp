#include "Obstacle.h"

RenderData Obstacle::getRenderData() const
{
    RenderData renderData;
    renderData.position = position;
    renderData.size = size;
    renderData.type = type;
    return renderData;
}

void Obstacle::onCollision(ICollidable* other)
{
}

