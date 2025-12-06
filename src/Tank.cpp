#include "Tank.h"
#include "Projectile.h"
#include "EntityManager.h" 
#include "Obstacle.h"
#include <iostream>

void Tank::update(float deltaTime)
{
	timeSinceLastShot += deltaTime;
	if (health <= 0) {
		isAlive = false;
	}
}

void Tank::shoot()
{
	if (timeSinceLastShot >= fireCooldown) {
		float tankHalfLength = size.y / 2;
		float projectileOffset = 5.0f;
		Vector2 projectileSpawn = position + direction * (tankHalfLength + projectileOffset);

		entityManager.addEntity(std::make_unique<Projectile>(projectileSpawn, direction, rotation));
		timeSinceLastShot = 0.0f;
	}
}

void Tank::takeDamage(int damage)
{
	health -= damage;
}

void Tank::heal(int healBonus)
{
	if (health < maxHealth) {
		health += healBonus;
	}
}

void Tank::onCollision(ICollidable* other)
{
	if (Obstacle* obstacle = dynamic_cast<Obstacle*>(other)) {
        Vector2 oPos = obstacle->getPosition();
        Vector2 oSize = obstacle->getSize();
        Vector2 tSize = getSize();

        Vector2 diff = position - oPos;

        float dx = (tSize.x / 2 + oSize.x / 2) - std::abs(diff.x);
        float dy = (tSize.y / 2 + oSize.y / 2) - std::abs(diff.y);

        if (dx > 0 && dy > 0) {
            if (dx < dy) {
                position.x += (diff.x > 0 ? dx : -dx);
            } 
			else {
                position.y += (diff.y > 0 ? dy : -dy);
            }
        }
	}
	else if (Projectile* p = dynamic_cast<Projectile*>(other)) {
		takeDamage(p->getDamage());
	}
}



