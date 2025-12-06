#include "GameLoop.h"

void GameLoop::run()
{
	gameManager.init();

	sf::Event event;
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			renderer.handleInput(event);
		}

		entityManager.updateAll(deltaTime);
		collisionManager.checkCollision();

		gameManager.update(deltaTime);

		renderer.getRenderable();
		renderer.draw();


		if (gameManager.getShouldReset()) {
			gameManager.reset();
			gameManager.setShouldReset(false);
		}
	}
}
