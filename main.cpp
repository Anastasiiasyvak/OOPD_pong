#include <SFML/Graphics.hpp>

int main() {
    sf::VideoMode VM(1280, 720);
    sf::RenderWindow window(VM, "Pong game by Nastusha");
    sf::Color backgroundColor(51, 102, 200);

    sf::CircleShape ball(15);
    ball.setFillColor(sf::Color(255, 140, 0));
    ball.setPosition(640, 360);

    float ballSpeedX = 0.3f;
    float ballSpeedY = 0.3f;

    float botSpeed = 0.25f;

    sf::RectangleShape verticalLine(sf::Vector2f(2.0f, VM.height));
    verticalLine.setFillColor(sf::Color::White);
    verticalLine.setPosition(VM.width / 2.0f, 0.0f);

    sf::RectangleShape horizontalLine(sf::Vector2f(VM.width, 2.0f));
    horizontalLine.setFillColor(sf::Color::White);
    horizontalLine.setPosition(0.0f, VM.height / 2.0f );

    sf::RectangleShape botPaddle(sf::Vector2f(20.0f, 150.0f));
    botPaddle.setFillColor(sf::Color(186, 22, 63));
    botPaddle.setPosition(50.0f, VM.height / 2.0f);

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        ball.move(ballSpeedX, ballSpeedY);

        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect paddleBounds = botPaddle.getGlobalBounds();

        if (ballBounds.intersects(paddleBounds)) {
            ballSpeedX = -ballSpeedX;
        }

        if (ball.getPosition().y < botPaddle.getPosition().y + botPaddle.getSize().y / 2.0f) {
            botPaddle.move(0.0f, -botSpeed);
        } else {
            botPaddle.move(0.0f, botSpeed);
        }

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
        window.draw(botPaddle);
        window.display();
    }

    return 0;
}
