#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class GameOver : public Engine::State
{
public:
    GameOver(std::shared_ptr<Context> &context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> context;
    sf::Text gameOverTitle;
    sf::Text retryButton;
    sf::Text exitButton;

    bool isRetryButtonSelected;
    bool isRetryButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
};

#endif // GAMEOVER_H
