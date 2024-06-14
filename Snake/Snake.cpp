#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

typedef enum {
    left,
    up,
    right,
    down
} direct;

int main(int argc, char* argv[])
{
    const int wWidth = 1280;
    const int wHeight = 720;
    const int snakeSpeed = 10.f;
    const int snakeSize = 10.f;
    const int foodSize = 10.f;
    const int bodySize = 10.f;
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(30);
    sf::CircleShape shape(snakeSize);
    sf::CircleShape food(foodSize);
    shape.setFillColor(sf::Color::Green);
    food.setFillColor(sf::Color::Red);

    std::cout << shape.getPosition().x << std::endl;
    std::cout << "hello world\n" << std::endl;

    sf::Font font;
    font.loadFromFile("C:\\Users\\gilbe\\Downloads\\Open_Sans\\static\\OpenSans-Light.ttf");
    sf::Text text;
    text.setFont(font);
    text.setPosition(100, 100);
    text.setString("Game Over");
    sf::Vector2f shapePosition(100.f, 100.f);

    int foodX = (rand() % (wWidth / foodSize  - foodSize)) * foodSize;
    int foodY = (rand() % (wHeight / foodSize - foodSize)) * foodSize;

    while (foodX == 100.f && foodY == 100.f) {
        foodX = (rand() % (wWidth / foodSize - foodSize)) * foodSize;
        foodY = (rand() % (wHeight / foodSize - foodSize)) * foodSize;
    }
 
    sf::Vector2f foodPosition(foodX, foodY);
    std::vector<sf::CircleShape> bodyShape;
    std::vector<sf::Vector2f> recodeSnake;

    sf::Vector2f temp;
    food.setPosition(foodPosition);
    direct snakeDirect = down;
    std::shared_ptr<sf::CircleShape> body;
    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        temp.x = shapePosition.x;
        temp.y = shapePosition.y;

        while (window.pollEvent(event))
        {
            // std::cout << "hi" << std::endl;
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
                snakeDirect = right;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
                snakeDirect = left;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                snakeDirect = up;
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                snakeDirect = down;
        }   

        switch (snakeDirect) {
        case left:
            shapePosition.x -= snakeSpeed;
            break;
        case up:
            shapePosition.y -= snakeSpeed;
            break;
        case right:
            shapePosition.x += snakeSpeed;
            break;
        case down:
            shapePosition.y += snakeSpeed;
            break;
        default:
            shapePosition.x = 0;
            shapePosition.y = 0;
            break;
        }
/*
        std::cout << "shape.x: " << shape.getPosition().x << std::endl;
        std::cout << "shape.y: " << shape.getPosition().y << std::endl;

        std::cout << "food.y: " << food.getPosition().x << std::endl;
        std::cout << "food.y: " << food.getPosition().y << std::endl
*/

        if (shapePosition.x == foodPosition.x &&
            shapePosition.y == foodPosition.y) {
            foodX = (rand() % (wWidth / foodSize - foodSize)) * foodSize;
            foodY = (rand() % (wHeight / foodSize - foodSize)) * foodSize;
            foodPosition.x = foodX;
            foodPosition.y = foodY;
            food.setPosition(foodPosition);
     
            recodeSnake.push_back(shapePosition);
            /*
            body = std::make_shared<sf::CircleShape>(10);
            body->setFillColor(sf::Color::Green);
            body->setPosition(50, 40);
     
            bodyShape.push_back(*body);
            */
        }

        if (recodeSnake.size()) {
        

            for (int i = recodeSnake.size() - 1; i > 0; i--) {
                recodeSnake[i].x = recodeSnake[i-1].x;
                recodeSnake[i].y = recodeSnake[i-1].y;
 
            }
            recodeSnake[0].x = temp.x;
            recodeSnake[0].y = temp.y;

            for (int i = 0; i < recodeSnake.size() - 1; i++) {
                shape.setPosition(recodeSnake[i].x, recodeSnake[i].y);
                // bodyShape[i].setPosition(recodeSnake[i].x, recodeSnake[i].y);
                // window.draw(bodyShape[i]);
                window.draw(shape);
            }
        }
 
        shape.setPosition(shapePosition);

        if (shapePosition.x > 1280 - snakeSize * 2 ||
            shapePosition.x < 0 ||
            shapePosition.y < 0 ||
            shapePosition.y > 720 - snakeSize * 2) {
            window.draw(text);
            window.display();
        }

        window.draw(shape);
        window.draw(food);
        window.display();
    }

    return 0;
}
