#include <SFML/Graphics.hpp>

class Ball{
private:
    sf::CircleShape ball;
    float speedX;
    float speedY;
public:
    Ball() : ball(15), speedX(0.3f), speedY(0.3f){
        ball.setFillColor(sf::Color(255, 140, 0));
        ball.setPosition(640, 360);
    }

    void move(){
        ball.move(speedX, speedY);
    }

    float getPositionX() const{
        return ball.getPosition().x;
    }

    float getPositionY() const {
        return ball.getPosition().y;
    }

    float getRadius() const {
        return ball.getRadius();
    }

    sf::FloatRect getGlobalBounds() const {
        return ball.getGlobalBounds();
    }

    void handleCollision(const sf::FloatRect& bounds){
        if (bounds.intersects(getGlobalBounds())){
            speedX = -speedX;
        }
    }

    void reverseSpeedX() {
        speedX = -speedX;
    }

    void reverseSpeedY(){
        speedY = -speedY;
    }

    sf::CircleShape& getShape(){
        return ball;
    }
};


class Paddle{
protected:
    sf::RectangleShape paddle;
    float speed;
public:
    Paddle(float width, float height, const sf::Color& color, float xPosition, float yPosition, float
    paddleSpeed)
    : paddle(sf::Vector2f(width, height)), speed(paddleSpeed){
        paddle.setFillColor(color);
        paddle.setPosition(xPosition, yPosition);
    }

    void moveUp(){
        paddle.move(0.0f, -speed);
    }
     void moveDown(){
        paddle.move(0.0f, speed);
    }

    sf::FloatRect getGlobalBounds() const {
        return paddle.getGlobalBounds();
    }

    sf::RectangleShape& getShape() {
        return paddle;
    }

    float getPositionY() const {
        return paddle.getPosition().y;
    }

    float getPositionX() const {
        return paddle.getPosition().y;
    }

    float getSizeY() const {
        return paddle.getSize().y;
    }
};

class BotPaddle : public Paddle{
public:
    BotPaddle()
    : Paddle(10.0f, 150.0f, sf::Color(186, 22, 63), 25.0f, 720 / 2.0f, 0.25f){}
};


class UserPaddle: public Paddle{
public:
    UserPaddle()
    : Paddle(10.0f, 150.0f, sf::Color(186, 22, 63), 1280 - 25.0f, 720 / 2.0f, 0.25f){}
};


class PongGame{

};

class Points{

};

class User{

};

class Screen{

};


class Message{

};



int main() {
    sf::VideoMode VM(1280, 720);
    sf::RenderWindow window(VM, "Pong game by Nastusha");
    sf::Color backgroundColor(51, 102, 200);

    Ball ball;
    BotPaddle botPaddle;
    UserPaddle userPaddle;



    sf::RectangleShape verticalLine(sf::Vector2f(2.0f, VM.height));
    verticalLine.setFillColor(sf::Color::White);
    verticalLine.setPosition(VM.width / 2.0f, 0.0f);

    sf::RectangleShape horizontalLine(sf::Vector2f(VM.width, 2.0f));
    horizontalLine.setFillColor(sf::Color::White);
    horizontalLine.setPosition(0.0f, VM.height / 2.0f);



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
                ball.move();

                sf::FloatRect ballBounds = ball.getGlobalBounds();
                sf::FloatRect botPaddleBounds = botPaddle.getGlobalBounds();
                sf::FloatRect userPaddleBounds = userPaddle.getGlobalBounds();

                if (ballBounds.intersects(botPaddleBounds) || ballBounds.intersects(userPaddleBounds)) {
                    ball.reverseSpeedX();
                }

                if (ball.getPositionY() < botPaddle.getPositionY() + botPaddle.getSizeY() / 2.0f) {
                    botPaddle.moveUp();
                } else {
                    botPaddle.moveDown();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && userPaddle.getPositionY() > 0) {
                    userPaddle.moveUp();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                    userPaddle.getPositionY() + userPaddle.getSizeY() < VM.height) {
                    userPaddle.moveDown();
                }

                if (ball.getPositionX() + (2 * ball.getRadius()) > VM.width || ball.getPositionX() < 0) {
                    ball.reverseSpeedX();

                    if (ball.getPositionX() < 0) {
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

                if (ball.getPositionY() + (2 * ball.getRadius()) > VM.height || ball.getPositionY() < 0) {
                    ball.reverseSpeedY();
                }
            }

            window.draw(verticalLine);
            window.draw(horizontalLine);
            window.draw(ball.getShape());
            window.draw(botPaddle.getShape());
            window.draw(userPaddle.getShape());
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
