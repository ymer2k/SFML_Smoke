#pragma once
#include <SFML/Graphics.hpp>

class Smoke
{
public:

	Smoke(sf::Vector2f pos = { 0.0f,0.0f }, sf::Vector2f vel = { 0,0 }, float radius = 0.0f, sf::Color color = { 0,0,0 }, sf::Time lifespanSeconds = sf::seconds(5));
	void setPos(sf::Vector2f pos);
	sf::Vector2f getPos();
	void setVel(sf::Vector2f vel);
	sf::Vector2f getVel();
	sf::Vector2f getAcc();
	void setRotationalPosition(float degrees);
	float getRotationalPosition();
	void setRotationalVelocity(float degreesPerSecond);
	float getRotationalVelocity();

	void setScale(sf::Vector2f scale);
	sf::Vector2f getScale();
	void setScaleRate(sf::Vector2f scaleRate);
	sf::Vector2f getScaleRate();


	void setRadius(float r);
	float getRadius();
	float getMass();
	bool isExpired();

	sf::Color getColor();
	sf::Sprite getShape();
	sf::Sprite& getShapeReference();

	float getAlpha();
	void setAlpha(float alpha);



private:
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Vector2f m_acc;
	sf::Color m_color;
	float m_rotationalPositionDegrees;
	float m_rotationalVelocityDegrees;
	sf::Vector2f m_scale;
	sf::Vector2f m_scaleRate;
	float m_mass;
	float m_radius;
	sf::Sprite m_shape;
	sf::Time m_lifespanSeconds;
	sf::Clock m_creationTime;
	float m_alpha;
};