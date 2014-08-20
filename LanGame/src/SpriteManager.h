#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

class TextureManager;
class StaticSprite;

class SpriteManager
{
    public:
        SpriteManager(const std::string &texturePath, sf::RenderWindow* renderWindow);
        SpriteManager(const char* texturePath, sf::RenderWindow* renderWindow);
        SpriteManager(const SpriteManager &other) = delete; // non construction-copyable
        SpriteManager &operator=(const SpriteManager &) = delete; // non copyable
        ~SpriteManager();

        void AddSprite(StaticSprite* sprite);
        void RemoveSprite(StaticSprite* sprite);
        void DrawSprites();

    protected:
    private:
        sf::RenderWindow* m_renderWindow;
        std::unique_ptr<TextureManager> m_textureManager;
        std::vector<StaticSprite*> m_staticSpriteDrawVec;
};

#endif