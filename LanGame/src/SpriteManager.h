#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

class TextureManager;
class BaseSprite;
class AnimSprite;

class SpriteManager
{
    public:
        SpriteManager(const std::string &texturePath, sf::RenderWindow* renderWindow);
        SpriteManager(const char* texturePath, sf::RenderWindow* renderWindow);
        SpriteManager(const SpriteManager &other) = delete; // non construction-copyable
        SpriteManager &operator=(const SpriteManager &) = delete; // non copyable
        ~SpriteManager();

        void AddSprite(BaseSprite* sprite);
        void RemoveSprite(BaseSprite* sprite);
        void AddSprite(AnimSprite* sprite);
        void RemoveSprite(AnimSprite* sprite);
        void DrawSprites();

    protected:
    private:
        void DrawBaseSprites();
        void DrawAnimSprites();

        sf::RenderWindow* m_renderWindow;
        std::unique_ptr<TextureManager> m_textureManager;
        std::vector<BaseSprite*> m_baseSpriteVec;
        std::vector<AnimSprite*> m_animSpriteVec;
};

#endif