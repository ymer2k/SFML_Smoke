#pragma once
#include <SFML/Graphics.hpp>


class Render
{
public:
	Render();

	sf::RenderWindow& getWindow();
	sf::RenderWindow m_window;
	sf::View m_view;

private:
	

};

