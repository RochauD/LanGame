#ifndef STATICSPRITE_H_
#define STATICSPRITE_H_

#include <string>
#include <SFML\Graphics.hpp>


class StaticSprite : sf::Sprite
{
    public:
        StaticSprite();
        StaticSprite(std::string filename);
        ~StaticSprite();

        std::string GetTextureName();
        void SetTextureName(const std::string &textureName);
    protected:
    private:
        std::string m_textureName;

};


#endif

