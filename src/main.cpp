#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <unordered_map>

int getRow(int numberOfRow);
sf::Image removeColor(sf::Image image, int width, int height, int r, int g, int b);

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

    float scaleX = 2;
    float scaleY = 2;

    void load(std::string path)
    {
        if (!image.loadFromFile(ASSETS_PATH + path))
            std::cout << "Could not load image: " << (ASSETS_PATH + path) << std::endl;

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

    void setFrame(int left, int top, int width, int height)
    {
        frame = sf::IntRect(left, top, width, height);
        sprite.setTextureRect(frame);
    }

    void removeBackground(int width, int heigth, int r, int g, int b)
    {
        texture.loadFromImage(removeColor(image, width, heigth, r, g, b));
    }
};

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Demo");
    sf::Event event;
    sf::Clock clock;

    //
    Entity bat;
    bat.speed = 300.0f;
    
    //w - s - d - a
    Entity buttons[4];

    /*The author of the image(" bat.png ")    is "Jetrel"    taken from URL(" https://opengameart.org/content/castle-platformer ") */
    /*The author of the image keys            is "Gerald"    taken from URL(" https://gerald-burke.itch.io/geralds-keys ") */

    //bat
    bat.load("bat.png");
    bat.removeBackground(171, 103, 111, 109, 81);
    bat.setFrame(getRow(0), 3, 30, 30);

    //button_w
    buttons[0].load("Gerald_Keys/Keys/W-Key.png");
    buttons[0].setFrame(0, 0, 32, 32);

    
    //button_s
    buttons[1].load("Gerald_Keys/Keys/S-Key.png");
    buttons[1].setFrame(0, 0, 32, 32);

    //button_d
    buttons[2].load("Gerald_Keys/Keys/D-Key.png");
    buttons[2].setFrame(0, 0, 32, 32);

    //button_a
    buttons[3].load("Gerald_Keys/Keys/A-Key.png");
    buttons[3].setFrame(0, 0, 32, 32);

    //setting bat to start at cener of the screen
    auto middleWidth = WIDTH / 4;
    auto middleHeight = WIDTH / 4;

    bat.x = middleWidth;
    bat.y = middleHeight - 128;
    buttons[0].sprite.setPosition(middleWidth, middleHeight - 30);
    buttons[1].sprite.setPosition(middleWidth, middleHeight + 64 - 30);
    buttons[2].sprite.setPosition(middleWidth + 64, middleHeight);
    buttons[3].sprite.setPosition(middleWidth - 64, middleHeight);

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

        //
        buttons[0].draw(window);
        buttons[1].draw(window);
        buttons[2].draw(window);
        buttons[3].draw(window);
        bat.draw(window);

        //
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
struct Animation
{
    sf::IntRect rect; //spritesheet rect
    int frames;       //number of frames
};
//    std::unordered_map<std::string, sf::IntRect> animations;
*/


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