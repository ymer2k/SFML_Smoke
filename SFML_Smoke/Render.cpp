#include "Render.h"

Render::Render()
{
	m_window.create(sf::VideoMode(1024, 768), "Smoke"); // The create  function is used when we create the window AFTER initilization.
	m_view = m_window.getView();
	m_view.setSize(1024, 768);
	m_window.setTitle("Smoke");
	m_window.setView(m_view);
}

sf::RenderWindow& Render::getWindow()
{
	return m_window;
}
