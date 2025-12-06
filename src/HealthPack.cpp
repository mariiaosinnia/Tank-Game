#include "HealthPack.h"
#include "Tank.h"

void HealthPack::interact(Tank* tank)
{
	tank->heal(healthBonus);
}

RenderData HealthPack::getRenderData() const
{
    RenderData renderData;
    renderData.position = getPosition();
    renderData.size = getSize();
    renderData.type = type;
    renderData.rotation = getRotation();
    return renderData;
}
