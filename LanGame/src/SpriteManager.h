#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>
#include <string>

class TextureManager;

class SpriteManager
{
    public:
        SpriteManager(const std::string &texturePath);
        SpriteManager(const char* texturePath);
        SpriteManager(const SpriteManager &other) = delete; // non construction-copyable
        SpriteManager &operator=(const SpriteManager &) = delete; // non copyable
        ~SpriteManager();

        bool AddSprite(T* sprite);
        bool RemoveSprite(T* sprite);

    protected:
    private:
        TextureManager* textureManager;
        std::vector<T> spriteArray;
};

#endif

