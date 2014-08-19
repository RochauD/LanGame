#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>
#include <string>
#include "StaticSprite.h"

class TextureManager;

class SpriteManager
{
    public:
        SpriteManager(const std::string &texturePath);
        SpriteManager(const char* texturePath);
        SpriteManager(const SpriteManager &other) = delete; // non construction-copyable
        SpriteManager &operator=(const SpriteManager &) = delete; // non copyable
        ~SpriteManager();

        bool AddSprite(StaticSprite* sprite);
        bool RemoveSprite(StaticSprite* sprite);

    protected:
    private:
        TextureManager* m_textureManager;
        std::vector<StaticSprite> m_spriteArray;
};

#endif

