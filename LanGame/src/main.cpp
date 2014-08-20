#include <SFML\Graphics.hpp>
#include "SpriteManager.h"
#include "BaseSprite.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");
    window.setVerticalSyncEnabled(true);

    SpriteManager mySpManager("", &window);
    bool x = true;

    BaseSprite testSprite("bild1.png");
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
                testSprite.Show(x = !x);

            }

        }

        window.clear();
        mySpManager.DrawSprites();
        window.display();
    }

    return 0;
}
