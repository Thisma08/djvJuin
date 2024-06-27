#include "PauseGame.h"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Context> &context) : context(context)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    // Texte
    pauseTitle.setFont(context->assets->GetFont(MAIN_FONT));
    pauseTitle.setString("Paused");
    pauseTitle.setCharacterSize(100);
    sf::FloatRect pauseBounds = pauseTitle.getLocalBounds();
    pauseTitle.setOrigin(pauseBounds.width / 2, pauseBounds.height / 2);
    pauseTitle.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);
}

void PauseGame::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            // Si "esc" pressé => Quitter l'état actuel
            case sf::Keyboard::Escape:
            {
                context->states->PopCurrent();
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void PauseGame::Update(const sf::Time &deltaTime)
{
}

// Dessiner les éléments
void PauseGame::Draw()
{
    context->window->draw(pauseTitle);
    context->window->display();
}
