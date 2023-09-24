#include "Smoke.h"


Smoke::Smoke(sf::Vector2f pos, sf::Vector2f vel, float radius, sf::Color color, sf::Time lifespanSeconds) :
	m_pos(pos)
	, m_vel(vel)
	, m_radius(radius)
	, m_color(color)
	, m_alpha(m_color.a)
	, m_lifespanSeconds(lifespanSeconds)
	, m_rotationalPositionDegrees(rand() % 360)
	, m_rotationalVelocityDegrees(100.0f)
	, m_scale(0.2f,0.2f)
	, m_scaleRate(1,1)

{
	m_shape.setPosition(m_pos);
	//m_shape.setRadius(m_radius);
	//m_shape.setPointCount(4);
	//m_shape.setFillColor(color);
	//m_shape.setOrigin(m_radius, m_radius);
	m_shape.setColor(color);
	m_mass = m_radius;
	m_creationTime = sf::Clock();
	m_shape.setRotation(m_rotationalPositionDegrees);
}


void Smoke::setPos(sf::Vector2f pos)
{
	m_pos = pos;
	m_shape.setPosition(m_pos);
}

sf::Vector2f Smoke::getPos()
{
	return m_pos;
}

void Smoke::setVel(sf::Vector2f vel)
{
	m_vel = vel;
}

sf::Vector2f Smoke::getVel()
{
	return m_vel;
}

void Smoke::setRotationalPosition(float degrees)
{
	m_rotationalPositionDegrees = degrees;
	m_shape.setRotation(m_rotationalPositionDegrees);
}

float Smoke::getRotationalPosition()
{
	return m_rotationalPositionDegrees;
}

void Smoke::setRotationalVelocity(float degreesPerSecond)
{
	m_rotationalVelocityDegrees = degreesPerSecond;
}

float Smoke::getRotationalVelocity()
{
	return m_rotationalVelocityDegrees;
}

void Smoke::setScale(sf::Vector2f scale)
{
	m_scale = scale;
	m_shape.setScale(m_scale);
}

sf::Vector2f Smoke::getScale()
{
	return m_scale;
}

void Smoke::setScaleRate(sf::Vector2f scaleRate)
{
	m_scaleRate = scaleRate;
}

sf::Vector2f Smoke::getScaleRate()
{
	return m_scaleRate;
}

void Smoke::setRadius(float r)
{
	m_radius = r;
}

float Smoke::getRadius()
{
	return m_radius;
}

float Smoke::getMass()
{
	return m_mass;
}

bool Smoke::isExpired() {
	sf::Time elapsedTime = m_creationTime.getElapsedTime();
	return elapsedTime >= m_lifespanSeconds;
}

sf::Sprite Smoke::getShape()
{
	return m_shape;
}

sf::Sprite& Smoke::getShapeReference()
{
	return m_shape;
}

float Smoke::getAlpha()
{
	return m_alpha;
}

void Smoke::setAlpha(float alpha)
{
	sf::Color fillColor = m_shape.getColor();
	m_alpha = alpha;
	m_shape.setColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, m_alpha));
}
