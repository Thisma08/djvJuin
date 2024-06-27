#include "MainMenu.h"
#include "Gameplay.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context) : context(context), isPlayButtonSelected(true), isPlayButtonPressed(false), isExitButtonSelected(false), isExitButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    // Ajouter police
    context->assets->AddFont(MAIN_FONT, "../../assets/fonts/AkaashNormal.ttf");

    // Titre
    gameTitle.setFont(context->assets->GetFont(MAIN_FONT));
    gameTitle.setString("SNAKE++");
    gameTitle.setCharacterSize(300);

    sf::FloatRect titleBounds = gameTitle.getLocalBounds();
    gameTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    gameTitle.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 300.f);

    // Bouton "Jouer"
    playButton.setFont(context->assets->GetFont(MAIN_FONT));
    playButton.setString("Play");
    playButton.setCharacterSize(50);

    sf::FloatRect playBounds = playButton.getLocalBounds();
    playButton.setOrigin(playBounds.width / 2, playBounds.height / 2);
    playButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 25.f);

    // Bouton "Quitter"
    exitButton.setFont(context->assets->GetFont(MAIN_FONT));
    exitButton.setString("Quit");
    exitButton.setCharacterSize(50);

    sf::FloatRect exitBounds = exitButton.getLocalBounds();
    exitButton.setOrigin(exitBounds.width / 2, exitBounds.height / 2);
    exitButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 + 50.f);
}

// Traitement de l'input du joueur
void MainMenu::ProcessInput()
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
            // Selection bouton
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!isPlayButtonSelected)
                {
                    isPlayButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!isExitButtonSelected)
                {
                    isPlayButtonSelected = false;
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                // Pressage bouton
                isPlayButtonPressed = false;
                isExitButtonPressed = false;

                if (isPlayButtonSelected)
                {
                    isPlayButtonPressed = true;
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
void MainMenu::Update(const sf::Time &deltaTime)
{
    // Changement de couleur des boutons en fct du choix
    if (isPlayButtonSelected)
    {
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color::Black);
    }

    // Bouton "Jouer" pressé
    if (isPlayButtonPressed)
    {
        context->states->Add(std::make_unique<Gameplay>(context), true);
    }
    // Bouton "Quitter" pressé
    else if (isExitButtonPressed)
    {
        context->states->PopAll();
    }
}

// Dessiner les éléments
void MainMenu::Draw()
{
    context->window->clear(sf::Color(18, 161, 5));
    context->window->draw(gameTitle);
    context->window->draw(playButton);
    context->window->draw(exitButton);
    context->window->display();
}

