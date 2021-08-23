#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

int main() {
	srand(time(NULL));
	//Define some constants
	const int screenWidth = 800;
	const int screenHeight = 800;
	const sf::Vector2f paddleSize(25, 100);
	const float ballRadius = 10.f;
	const float pi = 3.14159f;

	//Create the window of the application
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Pong !", sf::Style::Titlebar | sf::Style::Close);

	//Creat the left paddle
	sf::RectangleShape leftPaddle;
	leftPaddle.setSize(paddleSize);
	leftPaddle.setFillColor(sf::Color::Blue);
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(sf::Color(0, 0, 0));
	leftPaddle.setPosition(0, screenHeight / 2);
	leftPaddle.setOrigin(paddleSize / 2.f);

	//Create the right paddle
	sf::RectangleShape rightPaddle;
	rightPaddle.setSize(paddleSize);
	rightPaddle.setFillColor(sf::Color::Red);
	rightPaddle.setOutlineThickness(3);
	rightPaddle.setOutlineColor(sf::Color(0, 0, 0));
	rightPaddle.setPosition(screenWidth, screenHeight / 2);
	rightPaddle.setOrigin(paddleSize / 2.f);
	//Bot properties
	int botTarget = screenHeight / 2;
	float botPeriod = 0.2f;
	float botTimer = 0.f;

	//Create the ball
	sf::CircleShape ball;
	ball.setRadius(ballRadius);
	ball.setFillColor(sf::Color::Yellow);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setPosition(screenWidth / 2, screenHeight / 2);

	//Define the paddle properties
	float paddleSpeed = 400.f;

	//Define the ball properties
	const float ballSpeed = 400.f;
	float angleBall = -90.f;//to change

	//Load font
	sf::Font font;
	if (!font.loadFromFile("../Data/ARCADE.TTF")) return EXIT_FAILURE;

	//Init pause Messenger
	sf::Text pauseMessenger;
	pauseMessenger.setFont(font);
	pauseMessenger.setPosition(screenWidth / 2 - 200, screenHeight / 2);
	pauseMessenger.setFillColor(sf::Color::Green);
	pauseMessenger.setCharacterSize(50);
	pauseMessenger.setString("Press space to play");

	//Timer
	sf::Clock clock;
	float deltaTime = 0.f;
	//Game State
	bool isPlaying = false;

	//Sound
	sf::SoundBuffer ballSFX;
	ballSFX.loadFromFile("../Data/ball.wav");
	sf::Sound sfx;
	sfx.setBuffer(ballSFX);

	//Game loop
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (isPlaying == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			ball.setPosition(screenWidth / 2, screenHeight / 2);
			rightPaddle.setPosition(screenWidth, screenHeight / 2);
			leftPaddle.setPosition(0, screenHeight / 2);
			do {
				angleBall = rand() % 360;
			} while (angleBall < 45 || (angleBall > 135 && angleBall < 225) || angleBall>315);
			isPlaying = true;
		}
		if (isPlaying) {

			//the leftPaddle Moving
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sf::Vector2f pos = leftPaddle.getPosition();
				if (pos.y + paddleSize.y / 2 + paddleSpeed * deltaTime > screenHeight) leftPaddle.setPosition(pos.x, screenHeight - paddleSize.y / 2);
				else leftPaddle.move(0, paddleSpeed * deltaTime);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sf::Vector2f pos = leftPaddle.getPosition();
				if (pos.y - paddleSize.y / 2 - paddleSpeed * deltaTime < 0) leftPaddle.setPosition(pos.x, paddleSize.y / 2);
				else leftPaddle.move(0, -paddleSpeed * deltaTime);
			}
			//the rightPaddle Moving
			printf("%f\n", angleBall);
			//Update target of bot
			botTimer += deltaTime;
			if (botTimer >= botPeriod) {
				if (sin(angleBall * pi / 180) > 0.f) {
					botTarget = ball.getPosition().y;
					botTimer -= botPeriod;
				}
			}
			if (rightPaddle.getPosition().y + paddleSize.y / 4 < botTarget)//sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				sf::Vector2f pos = rightPaddle.getPosition();
				if (pos.y + paddleSize.y / 2 + paddleSpeed * deltaTime > screenHeight) rightPaddle.setPosition(pos.x, screenHeight - paddleSize.y / 2);
				else rightPaddle.move(0, 20 * paddleSpeed * deltaTime);
			}
			else if (rightPaddle.getPosition().y - paddleSize.y / 4 > botTarget)//sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				sf::Vector2f pos = rightPaddle.getPosition();
				if (pos.y - paddleSize.y / 2 - paddleSpeed * deltaTime < 0) rightPaddle.setPosition(pos.x, paddleSize.y / 2);
				else rightPaddle.move(0, -20 * paddleSpeed * deltaTime);
			}


			//the ball moving
			float factor = ballSpeed * deltaTime;
			//ball.move(cos(angleBall * pi / 180) * factor, sin(angleBall * pi / 180)*factor);
			ball.move(sin(angleBall * pi / 180) * factor, -cos(angleBall * pi / 180) * factor);

			//Check Collision Top_Down Wall
			if (ball.getPosition().y <= 0 || ball.getPosition().y >= screenHeight) {
				angleBall = 180.f - angleBall;
				sfx.play();
			}
			//Check Collison with the paddle
			//Left Paddle
			if (ball.getPosition().x - ballRadius <= leftPaddle.getPosition().x + paddleSize.x / 2
				&& ball.getPosition().y >= leftPaddle.getPosition().y - paddleSize.y / 2
				&& ball.getPosition().y <= leftPaddle.getPosition().y + paddleSize.y / 2
				&& ball.getPosition().x > leftPaddle.getPosition().x)
			{
				if (ball.getPosition().y > leftPaddle.getPosition().y) {
					angleBall = 360.f - angleBall + rand() % 10;
				}
				else {
					angleBall = 360.f - angleBall - rand() % 10;
				}
				sfx.play();

			}
			//Right Paddle
			if (ball.getPosition().x + ballRadius >= rightPaddle.getPosition().x - paddleSize.x / 2
				&& ball.getPosition().y >= rightPaddle.getPosition().y - paddleSize.y / 2
				&& ball.getPosition().y <= rightPaddle.getPosition().y + paddleSize.y / 2
				&& ball.getPosition().x < rightPaddle.getPosition().x)
			{
				if (ball.getPosition().y > rightPaddle.getPosition().y) {
					angleBall = 360.f - angleBall - rand() % 10;
				}
				else {
					angleBall = 360.f - angleBall + rand() % 10;
				}
				sfx.play();

			}
			if (ball.getPosition().x <= 0) {
				pauseMessenger.setString("Red is Winner\n Press space to play");
				isPlaying = false;
			}
			else if (ball.getPosition().x >= screenWidth) {
				pauseMessenger.setString("Blue is Winner\n Press space to play");
				isPlaying = false;
			}
		}

		window.clear(sf::Color::White);

		if (isPlaying) {
			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
		}
		else {
			window.draw(pauseMessenger);
		}
		window.display();
	}
}