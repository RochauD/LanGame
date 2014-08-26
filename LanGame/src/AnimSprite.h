#ifndef ANIMSPRITE_H_
#define ANIMSPRITE_H_

#include <string>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "BaseSprite.h"

class SpriteManager;
class TextureManager;

class AnimSprite : public BaseSprite
{
    public:
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

        virtual void AnimSprite::Draw(sf::RenderTarget* target);

    private:
        void CalcNextFrame();

        sf::Clock m_timer;
        sf::Time m_updateTime;
        bool m_isLooped;
        bool m_isPaused;
        sf::Vector2u m_currentPos;
        sf::Vector2u m_frameSize;
        int m_maxFrames;
        int m_currentFrame;
        int m_columns;
        int m_rows;
};

#endif

