#include "SpriteManager.h"
#include "TextureManager.h"
#include "BaseSprite.h"
#include "AnimSprite.h"


SpriteManager::SpriteManager(const std::string &texturePath, sf::RenderWindow* renderWindow)
{
    this->m_textureManager.reset(new TextureManager(texturePath));
    this->m_renderWindow = renderWindow;
    BaseSprite::SetSpriteManager(this);
    BaseSprite::SetTextureManager(this->m_textureManager.get());
}

SpriteManager::SpriteManager(const char* texturePath, sf::RenderWindow* renderWindow)
{
    this->m_textureManager.reset(new TextureManager(texturePath));
    this->m_renderWindow = renderWindow;
    BaseSprite::SetSpriteManager(this);
    BaseSprite::SetTextureManager(this->m_textureManager.get());
}

SpriteManager::~SpriteManager()
{

}

void SpriteManager::AddSprite(BaseSprite* sprite)
{
    this->m_baseSpriteVec.push_back(sprite);
}

void SpriteManager::RemoveSprite(BaseSprite* sprite)
{
    auto iter = this->m_baseSpriteVec.begin();
    for (iter; iter != this->m_baseSpriteVec.end(); iter++)
    {
        if (*iter == sprite)
        {
            this->m_baseSpriteVec.erase(iter);
            break;
        }
    }
}

void SpriteManager::Draw()
{
    auto iter = this->m_baseSpriteVec.begin();
    for (iter; iter != this->m_baseSpriteVec.end(); iter++)
    {
        (*iter)->Draw(this->m_renderWindow);
    }
}
