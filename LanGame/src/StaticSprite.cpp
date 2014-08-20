#include "StaticSprite.h"
#include "SpriteManager.h"
#include "TextureManager.h"

StaticSprite::StaticSprite() : sf::Sprite()
{

}
StaticSprite::StaticSprite(sf::Texture texture, bool show) : sf::Sprite(texture)
{
    this->m_visibilityFlag = show;
}
StaticSprite::StaticSprite(std::string filename, bool show) : sf::Sprite()
{
    sf::Texture* bufferTexturePtr = 0;
    this->m_textureName = filename;
    this->m_visibilityFlag = show;
    s_textureManager->GetTexture(this->m_textureName , &bufferTexturePtr); // @todo add exception
    this->setTexture(*bufferTexturePtr, true);
    s_spriteManager->AddSprite(this);
}
StaticSprite::~StaticSprite()
{
    s_spriteManager->RemoveSprite(this);
    s_textureManager->DeleteTexture(this->m_textureName);
}

std::string StaticSprite::GetTextureName()
{
    return this->m_textureName;
}

void StaticSprite::SetTextureName(const std::string &textureName)
{
    this->m_textureName = textureName;
}

void StaticSprite::Show(bool showFlag)
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

//static
SpriteManager* StaticSprite::s_spriteManager = 0;
TextureManager* StaticSprite::s_textureManager = 0;

void StaticSprite::SetSpriteManager(SpriteManager* spriteManager)
{
    s_spriteManager = spriteManager;
}

void StaticSprite::SetTextureManager(TextureManager* textureManager)
{
    s_textureManager = textureManager;
}

