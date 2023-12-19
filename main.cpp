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
    float userSpeed = 0.25f;

    sf::RectangleShape verticalLine(sf::Vector2f(2.0f, VM.height));
    verticalLine.setFillColor(sf::Color::White);
    verticalLine.setPosition(VM.width / 2.0f, 0.0f);

    sf::RectangleShape horizontalLine(sf::Vector2f(VM.width, 2.0f));
    horizontalLine.setFillColor(sf::Color::White);
    horizontalLine.setPosition(0.0f, VM.height / 2.0f);

    sf::RectangleShape botPaddle(sf::Vector2f(10.0f, 150.0f));
    botPaddle.setFillColor(sf::Color(186, 22, 63));
    botPaddle.setPosition(25.0f, VM.height / 2.0f);

    sf::RectangleShape userPaddle(sf::Vector2f(10.0f, 150.0f));
    userPaddle.setFillColor(sf::Color(186, 22, 63));
    userPaddle.setPosition(VM.width - 25.0f, VM.height / 2.0f);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(40);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("Press 1 for a short game (11 points)\nPress 2 for a long game (21 points)");
    menuText.setPosition(VM.width / 2.0f - 300.0f, VM.height / 2.0f - 50.0f);

    int gamePoints = 0;

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(VM.width / 2.0f - 20.0f, 10.0f);

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(40);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(VM.width / 2.0f, VM.height / 2.0f);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press SPACE to play again or Esc for close the game");
    restartText.setPosition(VM.width / 2.0f - 200.0f, VM.height / 2.0f + 100.0f);

    int userScore = 0;
    int botScore = 0;

    bool showMenu = true;
    bool isGameOver = false;
    bool restartRequested = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {  // Функція pollEvent викликає обробку однієї події за кожний виклик циклу
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (showMenu) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        gamePoints = 11;
                        showMenu = false;
                    } else if (event.key.code == sf::Keyboard::Num2) {
                        gamePoints = 21;
                        showMenu = false;
                    }
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space && isGameOver) {
                    restartRequested = true;
                }
            }
        }

        if (restartRequested) {
            userScore = 0;
            botScore = 0;
            isGameOver = false;
            showMenu = true;
            restartRequested = false;
            scoreText.setString("0 : 0");
        }

        window.clear(backgroundColor);

        if (showMenu) {
            window.draw(menuText);
        } else {
            if (!isGameOver) {
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                    userPaddle.getPosition().y + userPaddle.getSize().y < VM.height) {
                    userPaddle.move(0.0f, userSpeed);
                }

                if (ball.getPosition().x + (2 * ball.getRadius()) > VM.width || ball.getPosition().x < 0) {
                    ballSpeedX = -ballSpeedX;

                    if (ball.getPosition().x < 0) {
                        botScore++;
                    } else {
                        userScore++;
                    }

                    scoreText.setString(std::to_string(userScore) + " : " + std::to_string(botScore));
                }

                if (userScore == gamePoints || botScore == gamePoints) {
                    isGameOver = true;

                    if (userScore == gamePoints) {
                        resultText.setString("You lose!");
                    } else if (botScore == gamePoints) {
                        resultText.setString("You win!");
                    }
                }

                if (ball.getPosition().y + (2 * ball.getRadius()) > VM.height || ball.getPosition().y < 0) {
                    ballSpeedY = -ballSpeedY;
                }
            }

            window.draw(verticalLine);
            window.draw(horizontalLine);
            window.draw(ball);
            window.draw(botPaddle);
            window.draw(userPaddle);
            window.draw(scoreText);

            if (isGameOver) {
                window.draw(resultText);
                window.draw(restartText);
            }
        }

        window.display();
    }

    return 0;
}
