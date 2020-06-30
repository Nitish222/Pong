#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	//create a video mode obj
	VideoMode vm(1920, 1080);
	//create and open window for game
	RenderWindow window(vm, "PONG", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	//create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);
	//add ball
	Ball ball(1920 / 2, 0);
	//create HUD
	Text hud;

	//add fonts
	Font font;
	font.loadFromFile("Font/DIMIS___.ttf");
	//set the font to style
	hud.setFont(font);

	//make hud font big
	hud.setCharacterSize(75);
	hud.setPosition(20, 20);

	Clock clock;
	
	while (window.isOpen())
	{
		// Handle the player input // 
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				//Quit when window closed
				window.close();
			//handle quiting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			//handle movement input
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				bat.moveLeft();
			}
			else
			{
				bat.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				bat.moveRight();
			}
			else
			{
				bat.stopRight();
			}
		}
		// Update the bat, the ball and the HUD  //
		Time dt = clock.restart();
		bat.update(dt);
		ball.updateTime(dt);
		//update hud text
		std::stringstream ss;
		ss << "Score: " << score << " Lives:" << lives;
		hud.setString(ss.str());
		//handle ball collision to bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse the ball
			ball.reboundBottom();
			//remove life
			lives--;
			//check for zero lives
			if (lives < 1)
			{
				//reset the score
				score = 0;
				//reset lives
				lives = 3;
			}
		}
		//handle ball hiting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			//add the score
			score++;
		}
		//handle ball collision to sides
		if (ball.getPosition().left<0 || ball.getPosition().left + ball.getPosition().width>window.getSize().x)
		{
			ball.reboundSides();
		}
		//bat hitting the ball
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			//hit detected so reverse the ball
			ball.reboundBatOrTop();
		}
		// Draw the bat, the ball and the HUD //
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
		
	}
	return 0;
}