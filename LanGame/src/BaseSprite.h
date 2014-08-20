#ifndef BASESPRITE_H_
#define BASESPRITE_H_

#include <string>
#include <SFML\Graphics.hpp>

class SpriteManager;
class TextureManager;

class BaseSprite : public sf::Sprite
{
    public:
        BaseSprite();
        BaseSprite(std::string filename, bool show = true);
        ~BaseSprite();

        std::string GetTextureName();
        void SetTextureName(const std::string &textureName);
        void Show(bool showFlag = true);
        void SetTexture(std::string &filename);
        void setTexture(const sf::Texture &texture, bool resetRect = false) = delete;

        //static
        static void SetSpriteManager(SpriteManager* spriteManager);
        static void SetTextureManager(TextureManager* textureManager);
    protected:
    private:
        std::string m_textureName;
        bool m_visibilityFlag;

        //static
        static SpriteManager* s_spriteManager;
        static TextureManager* s_textureManager;
};

#endif
