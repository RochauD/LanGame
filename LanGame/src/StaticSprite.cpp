#include "StaticSprite.h"

StaticSprite::StaticSprite() : sf::Sprite()
{
}
StaticSprite::StaticSprite(std::string filename) : sf::Sprite()
{
    this->m_textureName = filename;
}
StaticSprite::~StaticSprite()
{
}

std::string StaticSprite::GetTextureName()
{
    return this->m_textureName;
}
void StaticSprite::SetTextureName(const std::string &textureName)
{
    this->m_textureName = textureName;
}