#include "Mine.h"
#include "Tank.h"

void Mine::interact(Tank* tank)
{
	tank->takeDamage(damage);
}

RenderData Mine::getRenderData() const
{
    RenderData renderData;
    renderData.position = getPosition();
    renderData.size = getSize();
    renderData.type = type;
    renderData.rotation = getRotation();
    return renderData;
}
