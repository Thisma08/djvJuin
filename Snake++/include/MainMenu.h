#ifndef MAINMENU_H
#define MAINMENU_H



#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> context;
    sf::Text gameTitle;
    sf::Text playButton;
    sf::Text exitButton;

    bool isPlayButtonSelected;
    bool isPlayButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};

#endif // MAINMENU_H
