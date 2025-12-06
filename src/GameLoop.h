#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "TankFactory.h"
#include "InteractiveObjectFactory.h"
#include "CollisionManager.h"
#include "Map.h"

class GameLoop {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    Map map;
    EntityManager entityManager;
    EventManager eventManager;
    Renderer renderer;
    TankFactory tankFactory;
    InteractiveObjectFactory interactiveObjectFactory;
    CollisionManager collisionManager;
    GameManager gameManager;

public:
    GameLoop() : window(sf::VideoMode(960, 720), "Tanks Game"),
        renderer(window, entityManager, eventManager, map),
        tankFactory(entityManager, eventManager),
        interactiveObjectFactory(),
        collisionManager(entityManager, map),
        gameManager(eventManager, entityManager, tankFactory, interactiveObjectFactory, &map) {}
    void run();
};
