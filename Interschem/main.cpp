#include <SFML/Graphics.hpp>
#include <iostream>

#define HEIGHT 576.f
#define WIDTH 1024.f

void createApp(sf::RenderWindow  &window) {
    sf::RectangleShape Background(sf::Vector2f(WIDTH, HEIGHT));
    Background.setFillColor(sf::Color(197, 201, 198));

    sf::RectangleShape Menu(sf::Vector2f(200.f, HEIGHT));
    Menu.setFillColor(sf::Color(120, 120, 120));

    sf::RectangleShape CreateButton(sf::Vector2f(200.f, 50.f));
    CreateButton.setFillColor(sf::Color(89, 235, 128));
    CreateButton.setPosition(0, HEIGHT - 50.f);

    window.draw(Background);
    window.draw(Menu);
    window.draw(CreateButton);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Interschem");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    std::cout<<"Lalalal";
                    break;
                default:
                        break;
            }
        }

        window.clear();
        createApp(window);
        window.display();

    }
    return 0;
}