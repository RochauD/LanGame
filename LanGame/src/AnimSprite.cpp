#include "AnimSprite.h"
#include "SpriteManager.h"
#include <iostream>

//static
SpriteManager* AnimSprite::s_spriteManager = 0;

void AnimSprite::SetSpriteManager(SpriteManager* spriteManager)
{
	AnimSprite::s_spriteManager = spriteManager;
}


//constructors & destructors

AnimSprite::AnimSprite(const std::string filename, const int framesPerRow, const int framesPerColumn, const sf::Time updateTime, bool paused, bool looped) 
{
	this->m_filename = filename;
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


	//this->setTexture(AnimSprite::s_spriteManager->AddSprite(filename));

	//this->SetFramesGrid(framesPerRow, framesPerColumn);
}


AnimSprite::~AnimSprite()
{

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

void AnimSprite::Show(bool showFlag)
{
	this->m_show = showFlag;
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