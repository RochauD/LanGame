#ifndef RACKET_H_
#define RACKET_H_

#include <SFML\Graphics.hpp>

class Racket
{
    public:
        Racket();
        ~Racket();
    protected:
    private:
        sf::Sprite m_racketSprite;
};

#endif
