////////////////////////////////////////////////////////////
//
// This class BaseSprite is based upon sf::Sprite but changed to allow easier inheritance
// and integration with managment classes.
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "BaseSprite.h"
#include "SpriteManager.h"
#include "TextureManager.h"

BaseSprite::BaseSprite(const std::string &filename, bool show)
{
    this->SetTexture(filename);
    this->m_visibilityFlag = show;
    if (this->m_visibilityFlag == true)
    {
        s_spriteManager->AddSprite(this);
    }
}

void BaseSprite::SetTexture(const std::string &filename)
{
    sf::Texture* bufferTexturePtr = 0;
    this->m_textureName = filename;
    s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr); // @todo add exception
    this->m_texture = bufferTexturePtr;
    SetTextureRect(sf::IntRect(0, 0, this->m_texture->getSize().x, this->m_texture->getSize().y));
}

void BaseSprite::SetTextureRect(const sf::IntRect &rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        UpdatePositions();
        UpdateTexCoords();
    }
}

void BaseSprite::SetColor(const sf::Color &color)
{
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

const sf::Texture* BaseSprite::GetTexture() const
{
    return m_texture;
}

const sf::IntRect &BaseSprite::GetTextureRect() const
{
    return m_textureRect;
}

const sf::Color &BaseSprite::GetColor() const
{
    return m_vertices[0].color;
}

sf::FloatRect BaseSprite::GetLocalBounds() const
{
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect BaseSprite::GetGlobalBounds() const
{
    return getTransform().transformRect(GetLocalBounds());
}

void BaseSprite::Draw(sf::RenderTarget* target)
{
    sf::RenderStates states;
    states.blendMode = sf::BlendAlpha;
    states.shader = 0;
    states.transform *= getTransform();
    states.texture = m_texture;
    target->draw(m_vertices, 4, sf::Quads, states);
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

void BaseSprite::UpdatePositions()
{
    sf::FloatRect bounds = GetLocalBounds();

    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(0, bounds.height);
    m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
    m_vertices[3].position = sf::Vector2f(bounds.width, 0);
}

void BaseSprite::UpdateTexCoords()
{
    float left = static_cast<float>(m_textureRect.left);
    float right = left + m_textureRect.width;
    float top = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    m_vertices[3].texCoords = sf::Vector2f(right, top);
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
