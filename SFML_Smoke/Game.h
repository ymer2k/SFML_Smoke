#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Smoke.h"


class Game
{
public:
	Game();

	void update(sf::Time dt, sf::RenderWindow& window);
	void drawGame(sf::RenderWindow& window);
	void interact(sf::RenderWindow& window);

	float M_PI = 3.14159265359;


private:
	sf::Event m_event;
	sf::CircleShape m_shape;
	sf::Vector2f m_shapeP;
	sf::Vector2f m_shapeV;
	sf::Vector2f m_shapeA;
	float m_shapeR;
	float m_g;
	int nrOfBalls;
	sf::Vector2f m_worldMousePos;
	sf::CircleShape m_triangle;
	sf::ConvexShape m_convexTriangle;

	std::vector<Smoke*> m_smokeObjects;
	sf::Texture m_smokeTexture;




	// methods
	void updateBallVelAndPos(Smoke& smoke, sf::Time dt);

};
