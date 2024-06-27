#include "AssetManager.h"

Engine::AssetManager::AssetManager()
{
}

Engine::AssetManager::~AssetManager()
{
}

// Ajout texture
void Engine::AssetManager::AddTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath))
    {
        texture->setRepeated(wantRepeated);
        textures[id] = std::move(texture);
    }
}

// Ajout police
void Engine::AssetManager::AddFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        fonts[id] = std::move(font);
    }
}

// Récupérer une texture
const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(textures.at(id).get());
}

// Récupérer une police
const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(fonts.at(id).get());
}
