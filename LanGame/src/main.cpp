#include <SFML\Graphics.hpp>
#include "TextureManager.h"

#include <functional>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");
    window.setVerticalSyncEnabled(true);

    TextureManager testManager("");
    sf::Texture* testTexPt = 0;
    testManager.GetTexture("bild1.png", &testTexPt);


    sf::Sprite testSprite;
    testSprite.setTexture(*testTexPt);
    testSprite.setPosition(0, 0);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
            {

            }

        }

        window.clear();
        window.draw(testSprite);
        window.display();
    }

    return 0;
}
