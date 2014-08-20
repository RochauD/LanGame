#include "AnimSprite.h"
#include "SpriteManager.h"
#include "TextureManager.h"

//constructors & destructors

AnimSprite::AnimSprite() : sf::Sprite()
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
                       bool looped) : sf::Sprite()
{
    sf::Texture* bufferTexturePtr = 0;
    this->m_textureName = filename;
    this->m_visibilityFlag = show;
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
    s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr); // @todo add exception
    sf::Sprite::setTexture(*bufferTexturePtr, true);
    s_spriteManager->AddSprite(this);
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
    this->m_frameSize = sf::Vector2i(this->getTexture()->getSize());
    this->m_frameSize.x /= this->m_rows;
    this->m_frameSize.y /= this->m_columns;
    this->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), this->m_frameSize));
}

std::string AnimSprite::GetTextureName()
{
    return this->m_textureName;
}

void AnimSprite::SetTextureName(const std::string &textureName)
{
    this->m_textureName = textureName;
}

void AnimSprite::Show(bool showFlag)
{
    if (this->m_visibilityFlag != showFlag)
    {
        if (showFlag == true)
        {
            s_spriteManager->AddSprite(this);
        }
        else
        {
            s_spriteManager->RemoveSprite(this);
        }
        this->m_visibilityFlag = showFlag;
    }
}

void AnimSprite::SetTexture(std::string &filename)
{
    sf::Texture* bufferTexturePtr = 0;
    s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr); // @todo add exception
    sf::Sprite::setTexture(*bufferTexturePtr, true);
    this->SetFramesGrid(this->m_rows, this->m_columns);
}

//private

void AnimSprite::CalcNextFrame()
{
    if (this->m_currentPos.x + 2 * this->m_frameSize.x <= this->getTexture()->getSize().x)
    {
        this->m_currentPos.x += this->m_frameSize.x;
    }
    else
    {
        this->m_currentPos.x = 0;

        if (this->m_currentPos.y + 2 * this->m_frameSize.y <= this->getTexture()->getSize().y)
        {
            this->m_currentPos.y += this->m_frameSize.y;
        }
        else
        {
            this->m_currentPos.y = 0;
        }
    }

    this->setTextureRect(sf::IntRect(this->m_currentPos, this->m_frameSize));
}

//static
SpriteManager* AnimSprite::s_spriteManager = 0;
TextureManager* AnimSprite::s_textureManager = 0;

void AnimSprite::SetSpriteManager(SpriteManager* spriteManager)
{
    s_spriteManager = spriteManager;
}

void AnimSprite::SetTextureManager(TextureManager* textureManager)
{
    s_textureManager = textureManager;
}