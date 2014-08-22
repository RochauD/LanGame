#include <SFML\Graphics.hpp>
#include "SpriteManager.h"
#include "BaseSprite.h"
#include "AnimSprite.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");
    window.setVerticalSyncEnabled(true);

    SpriteManager mySpManager("", &window);
    bool x = true;

    BaseSprite testSprite("bild1.png");
    testSprite.setPosition(0, 0);
    AnimSprite test2("bild2.png", true, 3,4, sf::milliseconds(1000/24), false, true);
    AnimSprite test3("bild3.png", true, 2, 4, sf::milliseconds(50), false, true);
    test3.setPosition(50, 50);
    AnimSprite test4("bild4.png", true, 5, 6, sf::milliseconds(50), false, true);
    test4.setPosition(500, 400);

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
        mySpManager.Draw();
        window.display();
    }

    return 0;
}
