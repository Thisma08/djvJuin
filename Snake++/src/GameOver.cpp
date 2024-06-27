#include "GameOver.h"
#include "Gameplay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context) : context(context), isRetryButtonSelected(true), isRetryButtonPressed(false), isExitButtonSelected(false), isExitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    // Titre
    gameOverTitle.setFont(context->assets->GetFont(MAIN_FONT));
    gameOverTitle.setString("Game Over");
    gameOverTitle.setCharacterSize(100);

    sf::FloatRect gameOverBounds = gameOverTitle.getLocalBounds();
    gameOverTitle.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
    gameOverTitle.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 200.f);

    // Bouton "Réessayer"
    retryButton.setFont(context->assets->GetFont(MAIN_FONT));
    retryButton.setString("Retry");
    retryButton.setCharacterSize(50);

    sf::FloatRect retryBounds = retryButton.getLocalBounds();
    retryButton.setOrigin(retryBounds.width / 2, retryBounds.height / 2);
    retryButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 25.f);

    // Bouton "Quitter"
    exitButton.setFont(context->assets->GetFont(MAIN_FONT));
    exitButton.setString("Quit");
    exitButton.setCharacterSize(50);

    sf::FloatRect exitBounds = exitButton.getLocalBounds();
    exitButton.setOrigin(exitBounds.width / 2, exitBounds.height / 2);
    exitButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 + 50.f);
}

// Traitement de l'input du joueur
void GameOver::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        // Si fenêtre quittée => Vider la pile des états
        if (event.type == sf::Event::Closed)
        {
            context->states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            // Sélection bouton
            case sf::Keyboard::Up:
            {
                if (!isRetryButtonSelected)
                {
                    isRetryButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!isExitButtonSelected)
                {
                    isRetryButtonSelected = false;
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Pressage bouton
                isRetryButtonPressed = false;
                isExitButtonPressed = false;

                if (isRetryButtonSelected)
                {
                    isRetryButtonPressed = true;
                }
                else
                {
                    isExitButtonPressed = true;
                }

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

// Maj de l'écran
void GameOver::Update(const sf::Time &deltaTime)
{
    // Changement de couleur des boutons en fct du choix
    if (isRetryButtonSelected)
    {
        retryButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
        retryButton.setFillColor(sf::Color::Black);
    }

    // Bouton "Réessayer" pressé
    if (isRetryButtonPressed)
    {
        // Retour au gameplay
        context->states->Add(std::make_unique<Gameplay>(context), true);
    }
    // Bouton "Quitter" pressé
    else if (isExitButtonPressed)
    {
        context->states->PopAll();
    }
}

// Dessiner les éléments
void GameOver::Draw()
{
    context->window->clear(sf::Color(18, 161, 5));
    context->window->draw(gameOverTitle);
    context->window->draw(retryButton);
    context->window->draw(exitButton);
    context->window->display();
}
