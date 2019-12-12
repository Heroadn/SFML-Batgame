#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <unordered_map>

int getRow(int numberOfRow);

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Demo");
    sf::Event event;
    sf::Clock clock;
    sf::Texture texture;
    sf::Sprite sprite;
    float x = 0.0f;
    float y = 0.0f;

    /*SPRITESHEET*/
    int row = getRow(0);
    sf::IntRect rectSourceSprite(row, 3, 30, 30);

    /*THE AUTHOR OF THEM IS Jetrel TAKEN FROM URL https://opengameart.org/content/castle-platformer*/
    if (texture.loadFromFile("assets/bat.png"))
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(rectSourceSprite);
        sprite.setScale(2, 2);
    }
    else {
        std::cout << "Could not load image" << std::endl;
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            //Handle events
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
            }

            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x = x - 0.1f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x = x + 0.1f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y = y - 0.1f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y = y + 0.1f;
        }

        if (clock.getElapsedTime().asSeconds()) {
            int limit = getRow(3);
            int index = clock.getElapsedTime().asSeconds();

            rectSourceSprite.left = getRow(index);
            sprite.setTextureRect(rectSourceSprite);   
        }

        //RESTART CLOCK
        if (clock.getElapsedTime().asSeconds() > 4.0f) {
            clock.restart();
        }


        sprite.setPosition(x, y);
        window.clear();
        window.draw(sprite);
        window.display();
    }

}

int getRow(int numberOfRow) {
    const int size = 34;
    int offset = 3;
    return (size * (int)numberOfRow) + offset;
}


/*    
    // If true, you will continue to receive keyboard events when a key is held down
    // If false, it will only fire one event per press until released
    window.setKeyRepeatEnabled(false);

    std::unordered_map<int, bool> keys;
    std::list<int> changedKeys;

    //RANDOW NUMBERS
    srand(time(NULL));               //seed random number generator with the current time
    auto randomNumber = rand() % 255;//generate a random number then confine it to a value of 0-255.
    std::uniform_int_distribution<int> randomColorRange(0, 255);
    std::random_device rd; //returns a random number to use as a seed for the mt algorithm
    std::mt19937 randomNumbers(rd()); //"shape" the results to our range
*/