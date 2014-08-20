#ifndef ANIMSPRITE_H_
#define ANIMSPRITE_H_

#include <string>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class SpriteManager;
class TextureManager;

class AnimSprite : public sf::Sprite
{
    public:
        AnimSprite();
        AnimSprite(const std::string filename, bool show = true, const int framesPerRow = 1, const int framesPerColumn = 1, const sf::Time updateTime = sf::seconds(1.0f), bool paused = true, bool looped = false);
        ~AnimSprite();

        void Play();
        void Pause();
        void Stop();
        void Update();

        bool IsLooped();
        bool IsPaused();
        int GetFramesPerRow();
        int GetFramesPerColumn();
        sf::Time GetUpdateTime();

        void SetLooped(const bool looped);
        void SetUpdateTime(const sf::Time updateTime);
        void SetFramesGrid(const int framesPerRow, const int framesPerColumn);

        std::string GetTextureName();
        void SetTextureName(const std::string &textureName);
        void Show(bool showFlag = true);
        void SetTexture(std::string &filename);
        void setTexture(const sf::Texture &texture, bool resetRect = false) = delete;

        //static
        static void SetSpriteManager(SpriteManager* spriteManager);
        static void SetTextureManager(TextureManager* textureManager);

    private:
        void CalcNextFrame();

        std::string m_textureName;
        bool m_visibilityFlag;
        sf::Clock m_timer;
        sf::Time m_updateTime;
        bool m_isLooped;
        bool m_isPaused;
        sf::Vector2i m_currentPos;
        sf::Vector2i m_frameSize;
        int m_maxFrames;
        int m_currentFrame;
        int m_columns;
        int m_rows;

        //static
        static SpriteManager* s_spriteManager;
        static TextureManager* s_textureManager;
};

#endif

