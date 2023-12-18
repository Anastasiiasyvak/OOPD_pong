#include <SFML/Graphics.hpp>

int main() {
    sf::VideoMode VM(1280, 720);
    sf::RenderWindow window(VM, "Pong game by Nastusha");
    sf::Color backgroundColor(51, 102, 200);

    sf::CircleShape ball(15);
    ball.setFillColor(sf::Color(255, 140, 0));
    ball.setPosition(640, 360);

    float ballSpeedX = 0.1f;
    float ballSpeedY = 0.1f;

    sf::RectangleShape verticalLine(sf::Vector2f(2.0f, VM.height)); // товщина і довжина vector2f числа параметри будуть  float
    verticalLine.setFillColor(sf::Color::White);
    verticalLine.setPosition(VM.width / 2.0f - 1.0f, 0.0f); // -1.0f, лінія її ширина, 0.0 це відступ зверху вікна

    sf::RectangleShape horizontalLine(sf::Vector2f(VM.width, 2.0f));
    horizontalLine.setFillColor(sf::Color::White);
    horizontalLine.setPosition(0.0f, VM.height / 2.0f - 1.0f); 

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        ball.move(ballSpeedX, ballSpeedY);

        if (ball.getPosition().x + (2 * ball.getRadius()) > VM.width || ball.getPosition().x < 0) {
            ballSpeedX = -ballSpeedX;
        }

        if (ball.getPosition().y + (2 * ball.getRadius()) > VM.height || ball.getPosition().y < 0) {
            ballSpeedY = -ballSpeedY;
        }

        window.clear(backgroundColor);
        window.draw(verticalLine);
        window.draw(horizontalLine);
        window.draw(ball);
        window.display();
    }

    return 0;
}
