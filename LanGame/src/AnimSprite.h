#ifndef ANIMSPRITE_H_
#define ANIMSPRITE_H_

#include <SFML\Graphics.hpp>
#include <string>
#include <SFML\System.hpp>

class SpriteManager;

class AnimSprite :
	public sf::Sprite
{
public:
	AnimSprite(const std::string filename, const int framesPerRow = 1, const int framesPerColumn = 1, const sf::Time updateTime = sf::seconds(1.0f), bool paused = true, bool looped = false);
	~AnimSprite();

	void Play();
	void Pause();
	void Stop();
	void Update();
	void Show(bool showFlag);

	bool IsLooped();
	bool IsPaused();
	int GetFramesPerRow();
	int GetFramesPerColumn();
	sf::Time GetUpdateTime();

	void SetLooped(const bool looped);
	void SetUpdateTime(const sf::Time updateTime);
	void SetFramesGrid(const int framesPerRow, const int framesPerColumn);

	static void SetSpriteManager(SpriteManager* spriteManager);

private:
	static SpriteManager* s_spriteManager;

	bool m_show;
	std::string m_filename;
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
	sf::Vertex m_vertices[4];

	void CalcNextFrame();
};

#endif

