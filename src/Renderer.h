#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "EventManager.h"
#include "IRenderable.h"
#include "Map.h"

enum class EntityTypes {
	PlayerTank,
	BotTank,
	HealthPack,
	Mine,
	Obstacle,
	Projectile,
	Unknown
};
class Renderer
{
private:
	sf::RenderWindow& window;
	EntityManager& entityManager;
	EventManager& eventManager;
	std::vector<IRenderable*> renderable;
	Map& map;

	sf::Texture playerTankTexture;
	sf::Texture botTankTexture;
	sf::Texture projectileTexture;
	sf::Texture healthPackTexture;
	sf::Texture mineTexture;

	float totalInitialBotHealth = 0.0f;
	bool botsHealthInitialized = false;
public:
	Renderer(sf::RenderWindow& win, EntityManager& entityM, EventManager& eventM, Map& m) : window(win), 
		entityManager(entityM), eventManager(eventM), map(m) {
		playerTankTexture.loadFromFile("Textures/player_tank.png");
		botTankTexture.loadFromFile("Textures/bot_tank.png");
		projectileTexture.loadFromFile("Textures/projectile.png");
		healthPackTexture.loadFromFile("Textures/health_pack.png");
		mineTexture.loadFromFile("Textures/mine.png");
	}
	void draw();
	void drawFrame(const RenderData& renderData, sf::RenderWindow& window);
	void handleInput(sf::Event& event);
    void drawVictoryScreen();
	void drawGameOverScreen();
	EntityTypes stringToEntityType(std::string& type);
	void drawHUD(const PlayerTank* player, const std::vector<BotTank*> bots);

	void getRenderable();
};

