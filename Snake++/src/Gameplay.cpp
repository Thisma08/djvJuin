#include "Gameplay.h"
#include "GameOver.h"
#include "PauseGame.h"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

Gameplay::Gameplay(std::shared_ptr<Context> &context) : context(context), score(0), snakeDirection({32.f, 0.f}), elapsedTime(sf::Time::Zero), isPaused(false)
{
    srand(time(nullptr));
}

Gameplay::~Gameplay()
{
}

void Gameplay::Init()
{
    // Ajout textures
    context->assets->AddTexture(GRASS, "../../assets/textures/grass.png", true);
    context->assets->AddTexture(FOOD, "../../assets/textures/food.png");
    context->assets->AddTexture(WALL, "../../assets/textures/wall.png", true);
    context->assets->AddTexture(SNAKE, "../../assets/textures/snake.png");

    // Application textures
    grass.setTexture(context->assets->GetTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    for (auto &wall : walls)
    {
        wall.setTexture(context->assets->GetTexture(WALL));
    }

    walls[0].setTextureRect({0, 0, (int)context->window->getSize().x, 32});
    walls[1].setTextureRect({0, 0, (int)context->window->getSize().x, 32});
    walls[1].setPosition(0, context->window->getSize().y - 32);

    walls[2].setTextureRect({0, 0, 32, (int)context->window->getSize().y});
    walls[3].setTextureRect({0, 0, 32, (int)context->window->getSize().y});
    walls[3].setPosition(context->window->getSize().x - 32, 0);

    food.setTexture(context->assets->GetTexture(FOOD));
    food.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);

    snake.Init(context->assets->GetTexture(SNAKE));

    // Affichage score
    scoreText.setFont(context->assets->GetFont(MAIN_FONT));
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setPosition(37, 32);
    scoreText.setCharacterSize(40);
}

// Traitement de l'input du joueur
void Gameplay::ProcessInput()
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
            sf::Vector2f newDirection = snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -32.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 32.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-32.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {32.f, 0.f};
                break;
            case sf::Keyboard::Escape:
                context->states->Add(std::make_unique<PauseGame>(context));
                break;

            default:
                break;
            }

            // Vérification nouvelle direction valide
            if (std::abs(snakeDirection.x) != std::abs(newDirection.x) || std::abs(snakeDirection.y) != std::abs(newDirection.y))
            {
                snakeDirection = newDirection;
            }
        }
    }
}

void Gameplay::Update(const sf::Time &deltaTime)
{
    if (!isPaused)
    {
        elapsedTime += deltaTime;

        if (elapsedTime.asSeconds() > 0.1)
        {
            for (auto &wall : walls)
            {
                // Si joueur touche mur => game over
                if (snake.IsOn(wall))
                {
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            // Si joueur touche nourriture
            if (snake.IsOn(food))
            {
                // Faire grandir le serpent
                snake.Grow(snakeDirection);

                // Générer nourriture à un autre endroit
                int x = 0, y = 0;
                x = std::clamp<int>(rand() % context->window->getSize().x, 32, context->window->getSize().x * 32);
                y = std::clamp<int>(rand() % context->window->getSize().y, 32, context->window->getSize().y * 32);

                food.setPosition(x, y);

                // Augmenter score
                score += 1;
                scoreText.setString("Score : " + std::to_string(score));
                scoreText.setCharacterSize(40);
            }
            else
            {
                // Bouger serpent
                snake.Move(snakeDirection);
            }

            // Si joueur collisione à lui-même => game over
            if (snake.IsSelfIntersecting())
            {
                context->states->Add(std::make_unique<GameOver>(context), true);
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

// Dessiner éléments
void Gameplay::Draw()
{
    context->window->clear();
    context->window->draw(grass);

    for (auto &wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);
    context->window->draw(scoreText);

    context->window->display();
}

void Gameplay::Pause()
{
    isPaused = true;
}

void Gameplay::Start()
{
    isPaused = false;
}

int Gameplay::getScore()
{
    return score;
}
