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
    AnimSprite::SetSpriteManager(this);
    AnimSprite::SetTextureManager(this->m_textureManager.get());
}

SpriteManager::SpriteManager(const char* texturePath, sf::RenderWindow* renderWindow)
{
    this->m_textureManager.reset(new TextureManager(texturePath));
    this->m_renderWindow = renderWindow;
    BaseSprite::SetSpriteManager(this);
    BaseSprite::SetTextureManager(this->m_textureManager.get());
    AnimSprite::SetSpriteManager(this);
    AnimSprite::SetTextureManager(this->m_textureManager.get());
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

void SpriteManager::AddSprite(AnimSprite* sprite)
{
    this->m_animSpriteVec.push_back(sprite);
}

void SpriteManager::RemoveSprite(AnimSprite* sprite)
{
    auto iter = this->m_animSpriteVec.begin();
    for (iter; iter != this->m_animSpriteVec.end(); iter++)
    {
        if (*iter == sprite)
        {
            this->m_animSpriteVec.erase(iter);
            break;
        }
    }
}

void SpriteManager::DrawSprites()
{
    DrawBaseSprites();
    DrawAnimSprites();
}

void SpriteManager::DrawBaseSprites()
{
    auto iter = this->m_baseSpriteVec.begin();
    for (iter; iter != this->m_baseSpriteVec.end(); iter++)
    {
        m_renderWindow->draw(**iter);
    }
}

void SpriteManager::DrawAnimSprites()
{
    auto iter = this->m_animSpriteVec.begin();
    for (iter; iter != this->m_animSpriteVec.end(); iter++)
    {
        (*iter)->Update();
        m_renderWindow->draw(**iter);
    }
}
