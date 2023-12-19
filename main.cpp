#include <SFML/Graphics.hpp>

int main() {
    sf::VideoMode VM(1280, 720);
    sf::RenderWindow window(VM, "Pong game by Nastusha");
    sf::Color backgroundColor(51, 102, 200);

    sf::CircleShape ball(15);
    ball.setFillColor(sf::Color(255, 140, 0));
    ball.setPosition(640, 360);

    float ballSpeedX = 0.5f;
    float ballSpeedY = 0.5f;

    float botSpeed = 0.3f;
    float userSpeed = 0.3f;

    sf::RectangleShape verticalLine(sf::Vector2f(2.0f, VM.height));
    verticalLine.setFillColor(sf::Color::White);
    verticalLine.setPosition(VM.width / 2.0f, 0.0f);

    sf::RectangleShape horizontalLine(sf::Vector2f(VM.width, 2.0f));
    horizontalLine.setFillColor(sf::Color::White);
    horizontalLine.setPosition(0.0f, VM.height / 2.0f );

    sf::RectangleShape botPaddle(sf::Vector2f(20.0f, 150.0f));
    botPaddle.setFillColor(sf::Color(186, 22, 63));
    botPaddle.setPosition(50.0f, VM.height / 2.0f);

    sf::RectangleShape userPaddle(sf::Vector2f(20.0f,150.0f));
    userPaddle.setFillColor(sf::Color(186,22, 63 ));
    userPaddle.setPosition(VM.width - 50.0f, VM.height / 2.0f);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        return EXIT_FAILURE;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(VM.width / 2.0f - 20.0f , 10.0f);

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(40);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(VM.width / 2.0f - 120.0f, VM.height / 2.0f - 20.0f);


    int userScore = 0;
    int botScore = 0;

    bool isGameOver = false;

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (!isGameOver){


            ball.move(ballSpeedX, ballSpeedY);

            sf::FloatRect ballBounds = ball.getGlobalBounds();
            sf::FloatRect botPaddleBounds = botPaddle.getGlobalBounds();
            sf::FloatRect userPaddleBounds = userPaddle.getGlobalBounds();

            if (ballBounds.intersects(botPaddleBounds) || ballBounds.intersects(userPaddleBounds)) {
                ballSpeedX = -ballSpeedX;
            }

            if (ball.getPosition().y < botPaddle.getPosition().y + botPaddle.getSize().y / 2.0f) {
                botPaddle.move(0.0f, -botSpeed);
            } else {
                botPaddle.move(0.0f, botSpeed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && userPaddle.getPosition().y > 0) {
                userPaddle.move(0.0f, -userSpeed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && userPaddle.getPosition().y + userPaddle.getSize().y < VM.height) {
                userPaddle.move(0.0f, userSpeed);
            }

            if (ball.getPosition().x + (2 * ball.getRadius()) > VM.width || ball.getPosition().x < 0) {
                ballSpeedX = -ballSpeedX;

                if (ball.getPosition().x<0){
                    botScore++;
                }
                else{
                    userScore++;
                }

                scoreText.setString(std::to_string(userScore) + " : " + std::to_string(botScore));
            }

            if (userScore == 11 || botScore == 11) {
                isGameOver = true;

                if (userScore == 11) {
                    resultText.setString("You lose! Press ESC to exit.");
                } else if (botScore == 11) {
                    resultText.setString("You win! Press ESC to exit.");
                } else {
                    resultText.setString("It's a draw! Press ESC to exit.");
                }
            }



            if (ball.getPosition().y + (2 * ball.getRadius()) > VM.height || ball.getPosition().y < 0) {
                ballSpeedY = -ballSpeedY;
            }

        }



        window.clear(backgroundColor);
        window.draw(verticalLine);
        window.draw(horizontalLine);
        window.draw(ball);
        window.draw(botPaddle);
        window.draw(userPaddle);
        window.draw(scoreText);
        window.draw(resultText);
        window.display();
    }

    return 0;
}
