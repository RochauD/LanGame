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

#ifndef BASESPRITE_H_
#define BASESPRITE_H_

#include <string>

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class SpriteManager;
class TextureManager;

class BaseSprite : public sf::Transformable
{
    public:
        BaseSprite(const std::string &filename, bool show = true);

        void SetTexture(const std::string &filename);
        void SetTextureRect(const sf::IntRect &rectangle);
        void SetColor(const sf::Color &color);
        const sf::Texture* GetTexture() const;
        const sf::IntRect &GetTextureRect() const;
        const sf::Color &GetColor() const;

        sf::FloatRect GetLocalBounds() const;
        sf::FloatRect GetGlobalBounds() const;

        virtual void BaseSprite::Draw(sf::RenderTarget* target);

        std::string GetTextureName();
        void SetTextureName(const std::string &textureName);
        void Show(bool showFlag = true);

        //static
        static void SetSpriteManager(SpriteManager* spriteManager);
        static void SetTextureManager(TextureManager* textureManager);

    protected:

        void UpdatePositions();
        void UpdateTexCoords();

        sf::Vertex m_vertices[4];
        const sf::Texture* m_texture;
        sf::IntRect m_textureRect;
        std::string m_textureName;
        bool m_visibilityFlag;

        //static
        static SpriteManager* s_spriteManager;
        static TextureManager* s_textureManager;
};




#endif
