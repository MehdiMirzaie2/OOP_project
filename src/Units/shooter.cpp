#include <SFML/Graphics.hpp>
#include <vector>


class Attack {
public:
    sf::CircleShape bullet;
    float speed;
    bool active;

    Attack(float x, float y, float speed = 2.0f) // increased bullet speed
        : bullet(3.f), speed(speed), active(true)
    {
        bullet.setFillColor(sf::Color::Red);
        bullet.setOrigin(-40.f, 40.f); 
        bullet.setPosition(x, y);
    }

    void update() {
        if (active) {
            bullet.move(speed, 0.f);
            if (bullet.getPosition().x > 1200) // window width 
                active = false;
        }
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "shooter");

    // textures
    sf::Texture unitTextureIdle;
    if (!unitTextureIdle.loadFromFile("gunmo1.png")) { // idle 
        return 1;
    }
    sf::Texture unitTextureMove;
    if (!unitTextureMove.loadFromFile("gunmo2.png")) { // moving 
        return 1;
    }

    sf::Sprite unitSprite(unitTextureIdle);
    unitSprite.setScale(0.2f, 0.2f); // adjust as need
    unitSprite.setPosition(-100, -100); 

    float unitX = -100;
    float unitY = -100;
    bool placed = false;
    bool moving = false;
    bool movingRight = true;

    // center origin
    sf::Vector2u texSize = unitTextureIdle.getSize();
    float spriteWidth = texSize.x * 0.2f;
    unitSprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);

    // container, attack
    std::vector<Attack> attacks;

    float moveSpeed = 0.08f; // movement speed

    // timer, fire
    sf::Clock fireClock;
    float fireInterval = 1.0f; // idle interval
    float moveFireInterval = 1.5f; // moving interval
    float currentFireInterval = fireInterval;

    // timer, animation
    sf::Clock animClock;
    float animInterval = moveFireInterval; // start with moving interval, will update below
    bool showIdle = true; // Start with idle frame

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // mouse click put sprite
            if (!placed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                unitX = event.mouseButton.x;
                unitY = event.mouseButton.y;
                unitSprite.setPosition(unitX, unitY);
                placed = true;
                moving = true;
                movingRight = true;
                fireClock.restart(); // start firing timer
                animClock.restart(); // sync animation and fire
                showIdle = true; // Ensure first frame is idle
                animInterval = fireInterval; // Start with idle interval
            }
        }

        // move horizontally
        if (moving) {
            // alternate
            if (animClock.getElapsedTime().asSeconds() > animInterval) {
                showIdle = !showIdle;
                animClock.restart();

                // Set timing for next frame
                if (showIdle) {
                    animInterval = fireInterval; // idle frame duration
                } else {
                    animInterval = moveFireInterval; // moving frame duration
                    // Only shoot when switching to moving PNG
                    attacks.emplace_back(unitX, unitY, 2.0f);
                }
            }

            // Set texture based on frame
            if (showIdle)
                unitSprite.setTexture(unitTextureIdle);
            else
                unitSprite.setTexture(unitTextureMove);

            unitX += moveSpeed; // moving speed
            if (unitX > window.getSize().x - spriteWidth / 2.0f) {
                unitX = window.getSize().x - spriteWidth / 2.0f;
                moving = false;
                showIdle = true;
                animInterval = fireInterval;
            }
            unitSprite.setPosition(unitX, unitY);
        } else if (placed) {
            unitSprite.setTexture(unitTextureIdle); // set idle texture
            showIdle = true;
            animInterval = fireInterval;
            // Do NOT shoot while idle
        }

        // update attacks
        for (auto& atk : attacks)
            atk.update();

        // remove inactive bullets
        attacks.erase(
            std::remove_if(attacks.begin(), attacks.end(), [](const Attack& atk) { return !atk.active; }),
            attacks.end()
        );

        window.clear(sf::Color::Transparent); 
        if (placed)
            window.draw(unitSprite);
        for (const auto& atk : attacks)
            if (atk.active)
                window.draw(atk.bullet);
        window.display();
    }

    return 0;
}