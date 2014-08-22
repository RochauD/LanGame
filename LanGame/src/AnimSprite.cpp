#include "AnimSprite.h"
#include "SpriteManager.h"
#include "TextureManager.h"

//constructors & destructors

AnimSprite::AnimSprite() : BaseSprite()
{
    this->m_visibilityFlag = false;
    this->m_rows = 1;
    this->m_columns = 1;
    this->m_updateTime = sf::seconds(1.0f);
    this->m_maxFrames = 0;
    this->m_currentFrame = 0;
    this->m_frameSize = sf::Vector2i(0, 0);
    this->m_currentPos = sf::Vector2i(0, 0);
    this->m_isPaused = true;
    this->m_isLooped = false;
    this->m_timer = sf::Clock();
}

AnimSprite::AnimSprite(const std::string filename,
                       bool show,
                       const int framesPerRow,
                       const int framesPerColumn,
                       const sf::Time updateTime,
                       bool paused,
                       bool looped) : BaseSprite(filename, show)
{
    this->m_rows = framesPerRow;
    this->m_columns = framesPerColumn;
    this->m_updateTime = updateTime;
    this->m_maxFrames = 0;
    this->m_currentFrame = 0;
    this->m_frameSize = sf::Vector2i(0, 0);
    this->m_currentPos = sf::Vector2i(0, 0);
    this->m_isPaused = paused;
    this->m_isLooped = looped;
    this->m_timer = sf::Clock();
    this->SetFramesGrid(framesPerRow, framesPerColumn);
}

AnimSprite::~AnimSprite()
{
    s_spriteManager->RemoveSprite(this);
    s_textureManager->DeleteTexture(this->m_textureName);
}

void AnimSprite::Play()
{
    this->m_isPaused = false;
    this->m_timer.restart();
}

void AnimSprite::Pause()
{
    this->m_isPaused = true;
}

void AnimSprite::Stop()
{
    this->m_isPaused = true;
    this->m_currentFrame = 0;
}

void AnimSprite::Update()
{
    if (!this->m_isPaused && this->m_timer.getElapsedTime() >= this->m_updateTime)
    {
        if (this->m_currentFrame + 1 > this->m_maxFrames)
        {


            if (!this->m_isLooped)
            {
                this->Stop();
            }
            this->m_currentFrame = 0;
        }

        this->CalcNextFrame();
        this->m_currentFrame++;

        this->m_timer.restart();
    }
}

//getter

bool AnimSprite::IsPaused()
{
    return this->m_isPaused;
}

bool AnimSprite::IsLooped()
{
    return this->m_isLooped;
}

int AnimSprite::GetFramesPerRow()
{
    return this->m_rows;
}

int AnimSprite::GetFramesPerColumn()
{
    return this->m_columns;
}

sf::Time AnimSprite::GetUpdateTime()
{
    return this->m_updateTime;
}


//setter

void AnimSprite::SetLooped(const bool looped)
{
    this->m_isLooped = looped;
}

void AnimSprite::SetUpdateTime(const sf::Time updateTime)
{
    this->m_updateTime = updateTime;
}

void AnimSprite::SetFramesGrid(const int framesPerRow, const int framesPerColumn)
{
    this->m_rows = framesPerRow;
    this->m_columns = framesPerColumn;
    this->m_maxFrames = this->m_rows * this->m_columns;
    this->m_frameSize = sf::Vector2i(this->GetTexture()->getSize());
    this->m_frameSize.x /= this->m_rows;
    this->m_frameSize.y /= this->m_columns;
    this->SetTextureRect(sf::IntRect(sf::Vector2i(0, 0), this->m_frameSize));
}


//private

void AnimSprite::CalcNextFrame()
{
    if (this->m_currentPos.x + 2 * this->m_frameSize.x <= this->GetTexture()->getSize().x)
    {
        this->m_currentPos.x += this->m_frameSize.x;
    }
    else
    {
        this->m_currentPos.x = 0;

        if (this->m_currentPos.y + 2 * this->m_frameSize.y <= this->GetTexture()->getSize().y)
        {
            this->m_currentPos.y += this->m_frameSize.y;
        }
        else
        {
            this->m_currentPos.y = 0;
        }
    }

    this->SetTextureRect(sf::IntRect(this->m_currentPos, this->m_frameSize));
}

void AnimSprite::Draw(sf::RenderTarget* target)
{
    this->Update();
    sf::RenderStates states;
    states.blendMode = sf::BlendAlpha;
    states.shader = 0;
    states.transform *= getTransform();
    states.texture = m_texture;
    target->draw(m_vertices, 4, sf::Quads, states);
}
