#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <unordered_map>

const int WIDTH  = 640;
const int HEIGHT = 480;

struct Entity
{
    sf::Sprite sprite;
    sf::Image image;
    sf::Texture texture;
    sf::IntRect frame;

    float x = 0.0f;
    float y = 0.0f;
    float speed = 0.0f;
};

int getRow(int numberOfRow);
sf::Image removeColor(sf::Image image, int width, int height, int r, int g, int b);

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Demo");
    sf::Event event;
    sf::Clock clock;

    //
    Entity bat;
    bat.speed = 300.0f;
    
    //
    Entity buttons[4];//w - s - d - a

    /*The author of the image(" bat.png ")    is "Jetrel"    taken from URL(" https://opengameart.org/content/castle-platformer ") */
    /*The author of the image keys            is "Gerald"    taken from URL(" https://gerald-burke.itch.io/geralds-keys ") */
    if (!bat.image.loadFromFile(ASSETS_PATH"bat.png"))
        std::cout << "Could not load image" << std::endl;

    if (!buttons[0].image.loadFromFile(ASSETS_PATH"Gerald_Keys/Keys/W-Key.png"))
        std::cout << "Could not load image" << std::endl;

    if (!buttons[1].image.loadFromFile(ASSETS_PATH"Gerald_Keys/Keys/S-Key.png"))
        std::cout << "Could not load image" << std::endl;

    if (!buttons[2].image.loadFromFile(ASSETS_PATH"Gerald_Keys/Keys/D-Key.png"))
        std::cout << "Could not load image" << std::endl;

    if (!buttons[3].image.loadFromFile(ASSETS_PATH"Gerald_Keys/Keys/A-Key.png"))
        std::cout << "Could not load image" << std::endl;

    //bat
    bat.frame = sf::IntRect(getRow(0), 3, 30, 30);
    bat.texture.loadFromImage(removeColor(bat.image, 171, 103, 111, 109, 81));
    bat.sprite.setTexture(bat.texture);
    bat.sprite.setTextureRect(bat.frame);
    bat.sprite.setScale(2, 2);

    //button_w
    buttons[0].frame = sf::IntRect(0, 0, 32, 32);
    buttons[0].texture.loadFromImage(buttons[0].image);
    buttons[0].sprite.setTexture(buttons[0].texture);
    buttons[0].sprite.setTextureRect(buttons[0].frame);
    buttons[0].sprite.setScale(2, 2);

    //button_s
    buttons[1].frame = sf::IntRect(0, 0, 32, 32);
    buttons[1].texture.loadFromImage(buttons[1].image);
    buttons[1].sprite.setTexture(buttons[1].texture);
    buttons[1].sprite.setTextureRect(buttons[1].frame);
    buttons[1].sprite.setScale(2, 2);

    //button_d
    buttons[2].frame = sf::IntRect(0, 0, 32, 32);
    buttons[2].texture.loadFromImage(buttons[2].image);
    buttons[2].sprite.setTexture(buttons[2].texture);
    buttons[2].sprite.setTextureRect(buttons[2].frame);
    buttons[2].sprite.setScale(2, 2);

    //button_a
    buttons[3].frame = sf::IntRect(0, 0, 32, 32);
    buttons[3].texture.loadFromImage(buttons[3].image);
    buttons[3].sprite.setTexture(buttons[3].texture);
    buttons[3].sprite.setTextureRect(buttons[3].frame);
    buttons[3].sprite.setScale(2, 2);

    //setting bat to start at cener of the screen
    bat.x = WIDTH / 2;
    bat.y = HEIGHT / 2;
    buttons[0].sprite.setPosition((WIDTH / 2), (HEIGHT / 2) - 30);
    buttons[1].sprite.setPosition((WIDTH / 2), (HEIGHT / 2) + 64 - 30);
    buttons[2].sprite.setPosition((WIDTH / 2) + 64, (HEIGHT / 2));
    buttons[3].sprite.setPosition((WIDTH / 2) - 64, (HEIGHT / 2));

    //timing
    sf::Clock delta;
    float dt = delta.restart().asSeconds();

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
            bat.x -= dt * bat.speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            bat.x += dt * bat.speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            bat.y -= dt * bat.speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            bat.y += dt * bat.speed;
        }

        if (clock.getElapsedTime().asSeconds()) {
            int limit = getRow(3);
            int index = clock.getElapsedTime().asSeconds();

            bat.frame.left = getRow(index);
            bat.sprite.setTextureRect(bat.frame);
        }

        //RESTART CLOCK
        if (clock.getElapsedTime().asSeconds() > 4.0f) {
            clock.restart();
        }

        //
        bat.sprite.setPosition(bat.x, bat.y);

        //
        window.clear(sf::Color::White);
        window.draw(buttons[0].sprite);
        window.draw(buttons[1].sprite);
        window.draw(buttons[2].sprite);
        window.draw(buttons[3].sprite);

        window.draw(bat.sprite);
        window.display();
        dt = delta.restart().asSeconds();
    }

}

int getRow(int numberOfRow) {
    const int size = 34;
    int offset = 3;
    return (size * (int)numberOfRow) + offset;
}

sf::Image removeColor(sf::Image image,int width, int height, int r, int g, int b) {

    for (int y = 0; y < height; y++) {
        //removing pixels
        for (int x = 0; x < width; x++) {
            int pr = image.getPixel(x, y).r == r;
            int pg = image.getPixel(x, y).g == g;
            int pb = image.getPixel(x, y).b == b;

            if (pr  && pg  && pb ) {    
                 image.setPixel(x, y, sf::Color(0,0,0,0));
            }
        }
    }

    return image;
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