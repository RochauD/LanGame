#include "BaseSprite.h"
#include "SpriteManager.h"
#include "TextureManager.h"

BaseSprite::BaseSprite() : sf::Sprite()
{

}
BaseSprite::BaseSprite(std::string filename, bool show) : sf::Sprite()
{
    sf::Texture* bufferTexturePtr = 0;
    this->m_textureName = filename;
    this->m_visibilityFlag = show;
    s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr); // @todo add exception
    sf::Sprite::setTexture(*bufferTexturePtr, true);
    s_spriteManager->AddSprite(this);
}
BaseSprite::~BaseSprite()
{
    s_spriteManager->RemoveSprite(this);
    s_textureManager->DeleteTexture(this->m_textureName);
}

std::string BaseSprite::GetTextureName()
{
    return this->m_textureName;
}

void BaseSprite::SetTextureName(const std::string &textureName)
{
    this->m_textureName = textureName;
}

void BaseSprite::Show(bool showFlag)
{
    if (this->m_visibilityFlag != showFlag)
    {
        if (showFlag == true)
        {
            s_spriteManager->AddSprite(this);
        }
        else
        {
            s_spriteManager->RemoveSprite(this);
        }
        this->m_visibilityFlag = showFlag;
    }
}

void BaseSprite::SetTexture(std::string &filename)
{
    sf::Texture* bufferTexturePtr = 0;
    s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr); // @todo add exception
    sf::Sprite::setTexture(*bufferTexturePtr, true);
}

//static
SpriteManager* BaseSprite::s_spriteManager = 0;
TextureManager* BaseSprite::s_textureManager = 0;

void BaseSprite::SetSpriteManager(SpriteManager* spriteManager)
{
    s_spriteManager = spriteManager;
}

void BaseSprite::SetTextureManager(TextureManager* textureManager)
{
    s_textureManager = textureManager;
}

