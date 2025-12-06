# Tank Game

2D tank combat game featuring bot AI, collision detection, and event-driven architecture.

## Features
- Player vs Bot combat system
- Event-driven game architecture (EventManager, EventPublisher/Listener pattern)
- Entity Component System (EntityManager, EntityFactory)
- Collision detection (CollisionManager)
- Interactive objects (HealthPacks, Mines)

## Technical Implementation
- **Language:** C++ with OOP principles
- **Architecture:** 
  - Entity-Component System
  - Factory Pattern for entity creation
  - Event-driven design
  - Interface segregation (IEntity, ICollidable, IRenderable)
- **Graphics:** SFML

## Code Structure
```
src/
├── GameManager.cpp/h      - Main game controller
├── GameLoop.cpp/h         - Game loop implementation
├── EntityManager.cpp/h    - Entity lifecycle management
├── EventManager.cpp/h     - Event system
├── CollisionManager.cpp/h - Collision detection
├── Renderer.cpp/h         - Graphics rendering
├── Tank.cpp/h             - Base tank class
├── PlayerTank.cpp/h       - Player-controlled tank
├── BotTank.cpp/h          - AI opponent
├── Projectile.cpp/h       - Bullet system
└── InteractiveObject.h    - Base for pickups
```

## Design Patterns Used
- **Factory Pattern:** TankFactory, InteractiveObjectFactory
- **Observer Pattern:** Event system (IEventListener, IEventPublisher)
- **Interface Segregation:** Multiple interfaces for different behaviors
