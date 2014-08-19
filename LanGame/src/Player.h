#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "Racket.h"

class Player
{
    public:
        Player();
        Player(std::string &name);
        ~Player();
    protected:
    private:
        std::string m_name;
        int m_lives;
        int m_color;
        Racket M_racket;
};

#endif
