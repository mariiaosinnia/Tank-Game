#include "Renderer.h"
#include "IRenderable.h"
#include <iostream>

void Renderer::draw()
{
	PlayerTank* playerTank = entityManager.getPlayer();
	std::vector<BotTank*> bots = entityManager.getBots();
	window.clear();
	for (auto& obj : renderable) {
		drawFrame(std::move(obj->getRenderData()), window); 
	}
	if (playerTank && !bots.empty()) {
		drawHUD(playerTank, bots);
	}
	window.display();
}

void Renderer::drawFrame(const RenderData& renderData, sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	rect.setOrigin(renderData.size.x / 2, renderData.size.y / 2);
	rect.setPosition(renderData.position.x, renderData.position.y);
	rect.setSize({ renderData.size.x, renderData.size.y });
	rect.setRotation(renderData.rotation);
	std::string type = renderData.type;
	EntityTypes entityType = stringToEntityType(type);
	switch (entityType) {
		case EntityTypes::PlayerTank:
			rect.setTexture(&playerTankTexture);
			break;
		case EntityTypes::BotTank:
			rect.setTexture(&botTankTexture);
			break;
		case EntityTypes::HealthPack:
			rect.setTexture(&healthPackTexture);
			break;
		case EntityTypes::Mine:
			rect.setTexture(&mineTexture);
			break;
		case EntityTypes::Obstacle:
			rect.setFillColor(sf::Color::White);
			break;
		case EntityTypes::Projectile:
			rect.setTexture(&projectileTexture);
			break;
		case EntityTypes::Unknown:
			rect.setFillColor(sf::Color::White);
			break;
	}
	window.draw(rect);
}

void Renderer::handleInput(sf::Event& event)
{
	EventType gameEvent = EventType::None;
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::W: 
			gameEvent = EventType::MovingForward; 
			break;
		case sf::Keyboard::S: 
			gameEvent = EventType::MovingBackward; 
			break;
		case sf::Keyboard::A: 
			gameEvent = EventType::TurnLeft; 
			break;
		case sf::Keyboard::D: 
			gameEvent = EventType::TurnRight; 
			break;
		case sf::Keyboard::Space: 
			gameEvent = EventType::Shoot; 
			break;
		default: break;
		}
	}
	else if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::W: 
			gameEvent = EventType::StopForward; 
			break;
		case sf::Keyboard::S: 
			gameEvent = EventType::StopBackward; 
			break;
		case sf::Keyboard::A: 
			gameEvent = EventType::StopTurnLeft; 
			break;
		case sf::Keyboard::D: 
			gameEvent = EventType::StopTurnRight; 
			break;
		default: break;
		}
	}

	if (gameEvent != EventType::None) {
		eventManager.notify(gameEvent);
	}
}

void Renderer::getRenderable()
{
	renderable.clear();
	const std::vector<std::unique_ptr<IEntity>>& entities = entityManager.getEntities();
	for (const auto& entity : entities) {
		if (IRenderable* r = dynamic_cast<IRenderable*>(entity.get())) {
			renderable.push_back(r);
		}
	}
	const std::vector<std::unique_ptr<ICollidable>>& obstacles = map.getObstacles();
	for (const auto& obstacle : map.getObstacles()) {
		IRenderable* r = dynamic_cast<IRenderable*>(obstacle.get());
		renderable.push_back(r);
	}
}

void Renderer::drawVictoryScreen()
{
	window.clear(sf::Color::Green);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setString("Victory!");
	text.setPosition(400, 300);

	window.draw(text);
	window.display();
}

void Renderer::drawGameOverScreen()
{
	window.clear(sf::Color::Red);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	text.setString("Game Over!");
	text.setPosition(400, 300);

	window.draw(text);
	window.display();
}

EntityTypes Renderer::stringToEntityType(std::string& type)
{
	if (type == "playerTank") {
		return EntityTypes::PlayerTank;
	}
	else if (type == "botTank") {
		return EntityTypes::BotTank;
	}
	else if (type == "mine") {
		return EntityTypes::Mine;
	}
	else if (type == "healthPack") {
		return EntityTypes::HealthPack;
	}
	else if (type == "obstacle") {
		return EntityTypes::Obstacle;
	}
	else if (type == "projectile") {
		return EntityTypes::Projectile;
	}
	else {
		return EntityTypes::Unknown;
	}
}
void Renderer::drawHUD(const PlayerTank* player, const std::vector<BotTank*> bots)
{
	const float HUD_MARGIN_X = 20.0f;          
	const float HUD_TOP_OFFSET = 50.0f;        
	const float HUD_BAR_WIDTH = 200.0f;        
	const float HUD_BAR_HEIGHT = 20.0f;         
	const int HUD_FONT_SIZE = 25;              

	const sf::Color HUD_BG_COLOR(50, 50, 50);  
	const sf::Color PLAYER_HEALTH_COLOR = sf::Color::Green;
	const sf::Color BOT_HEALTH_COLOR = sf::Color::Red;
	const sf::Color PLAYER_TEXT_COLOR = sf::Color::White;
	const sf::Color BOT_TEXT_COLOR = sf::Color::White;

	float screenWidth = static_cast<float>(window.getSize().x);
	float playerRatio = std::max(0.f, player->getHealth() / static_cast<float>(player->getMaxHealth()));

	if (!botsHealthInitialized) {
		for (auto* bot : bots) {
			totalInitialBotHealth += bot->getMaxHealth();
		}
		botsHealthInitialized = true;
	}

	float totalCurrentHealth = 0.0f;
	for (auto* bot : bots) {
		totalCurrentHealth += bot->getHealth();
	}

	float avgRatio = totalCurrentHealth / totalInitialBotHealth;

	sf::RectangleShape playerBack({ HUD_BAR_WIDTH, HUD_BAR_HEIGHT });
	playerBack.setFillColor(HUD_BG_COLOR);
	playerBack.setPosition(HUD_MARGIN_X, HUD_TOP_OFFSET);

	sf::RectangleShape playerFront({ HUD_BAR_WIDTH * playerRatio, HUD_BAR_HEIGHT });
	if (playerRatio < 0.25f) {
		playerFront.setFillColor(sf::Color::Red);
	}
	else if (playerRatio < 0.5f) {
		playerFront.setFillColor(sf::Color::Yellow);
	}
	else {
		playerFront.setFillColor(PLAYER_HEALTH_COLOR);
	}
	playerFront.setPosition(HUD_MARGIN_X, HUD_TOP_OFFSET);

	sf::RectangleShape botBack({ HUD_BAR_WIDTH, HUD_BAR_HEIGHT });
	botBack.setFillColor(HUD_BG_COLOR);
	botBack.setPosition(screenWidth - HUD_BAR_WIDTH - HUD_MARGIN_X, HUD_TOP_OFFSET);

	sf::RectangleShape botFront({ HUD_BAR_WIDTH * avgRatio, HUD_BAR_HEIGHT });
	if (avgRatio < 0.25f) {
		botFront.setFillColor(sf::Color(100, 0, 0));
	}
	else if (avgRatio < 0.5f) {
		botFront.setFillColor(sf::Color(255, 140, 0));
	}
	else {
		botFront.setFillColor(BOT_HEALTH_COLOR);
	}
	botFront.setPosition(screenWidth - HUD_BAR_WIDTH - HUD_MARGIN_X, HUD_TOP_OFFSET);

	sf::Font font;
	font.loadFromFile("Fonts/ByteBounce.ttf");

	sf::Text playerText("Player", font, HUD_FONT_SIZE);
	playerText.setFillColor(PLAYER_TEXT_COLOR);
	playerText.setPosition(HUD_MARGIN_X, HUD_TOP_OFFSET - HUD_FONT_SIZE - 2);

	sf::Text botText("Bot", font, HUD_FONT_SIZE);
	botText.setFillColor(BOT_TEXT_COLOR);
	botText.setPosition(screenWidth - HUD_BAR_WIDTH - HUD_MARGIN_X, HUD_TOP_OFFSET - HUD_FONT_SIZE - 2);

	window.draw(playerBack);
	window.draw(playerFront);
	window.draw(botBack);
	window.draw(botFront);
	window.draw(playerText);
	window.draw(botText);
}



