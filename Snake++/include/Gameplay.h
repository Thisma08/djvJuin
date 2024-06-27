#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.h"
#include "State.h"
#include "Snake.h"

class Gameplay : public Engine::State
{
public:
    Gameplay(std::shared_ptr<Context> &context);
    ~Gameplay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
    int getScore();

private:
    std::shared_ptr<Context> context;
    sf::Sprite grass;
    sf::Sprite food;
    std::array<sf::Sprite, 4> walls;
    Snake snake;

    sf::Text scoreText;
    int score;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;

    bool isPaused;
};
#endif // GAMEPLAY_H
