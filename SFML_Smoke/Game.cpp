#include "Game.h"
#include "math.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <random>


Game::Game():
    m_shapeP(100,100)
    , m_shapeV(0,0)
    , m_shapeA(0,0)
    , m_shapeR(50)
    , m_g(400)
    , nrOfBalls(0)
{
    m_convexTriangle.setPointCount(3);

    // Define the vertices for the longer sides and the shorter base side
    sf::Vector2f topVertex(0, -40);          // Top vertex (twice as long)
    sf::Vector2f leftVertex(-20, 20);        // Left vertex (twice as long)
    sf::Vector2f rightVertex(20, 20);        // Right vertex (base side)

    m_convexTriangle.setPoint(0, topVertex);
    m_convexTriangle.setPoint(1, leftVertex);
    m_convexTriangle.setPoint(2, rightVertex);

    m_convexTriangle.setFillColor(sf::Color::White);

    // Set the initial position of the triangle
    m_convexTriangle.setPosition(30, 400);

    // Set the origin to the center of the triangle
    m_convexTriangle.setOrigin(0, 10); // Half of the height of the longer sides
    m_convexTriangle.setFillColor(sf::Color(255, 255, 255, 126));

    //Load texture
    if (!m_smokeTexture.loadFromFile("resources/smoke.png"))
    {
        std::cout << "TEXTURE LOAD ERROR" << std::endl;
    }


}

void Game::update(sf::Time dt, sf::RenderWindow& window) //Update objects position, rotation etc
{

    // Calculate the angle between the ´convex triangle and the mouse
    float angle = std::atan2(m_worldMousePos.y - m_convexTriangle.getPosition().y, m_worldMousePos.x - m_convexTriangle.getPosition().x);
    angle = angle * 180.0f / (M_PI);
    //std::cout << angle + 90.0f << std::endl;
    m_convexTriangle.setRotation(angle + 90.0f);


    // update state of smoke
    for (auto it = m_smokeObjects.begin(); it != m_smokeObjects.end(); ) {

        //update position and velocity.
        Smoke* smokePointer = *it;
        updateBallVelAndPos(*smokePointer, dt);


        // Decrease the alpha component over time (put into function)
        float alpha = smokePointer->getAlpha();
        if (alpha > 0.0f) {
            alpha *= 0.98; // Decrease the alpha value
            smokePointer->setAlpha(alpha);
        }

        // Change scale #1
   /*     sf::Vector2f scale = smokePointer->getShapeReference().getScale();
        smokePointer->getShapeReference().setScale(scale*1.016f);*/

        //Change scale #2
        sf::Vector2f scale = smokePointer->getScale();
        sf::Vector2f scaleRate = smokePointer->getScaleRate();
        float scaleRateChange = 1.0f; //1.01f;
        smokePointer->setScaleRate(scaleRate * scaleRateChange);
        smokePointer->setScale(scale + scaleRate * scaleRateChange*dt.asSeconds());



        //add Rotation
        //float rotation = smokePointer->getShapeReference().getRotation();
        //rotation *= 0.99f;
        //if (rotation < 1)
        //    rotation += 360;
        //smokePointer->getShapeReference().setRotation(rotation);


        // add rotation #2
        float rotationPosition = smokePointer->getRotationalPosition();
        float rotationVelocity = smokePointer->getRotationalVelocity();
        float friction = 0.975f;
        float newRotationVel = rotationVelocity * friction;
        smokePointer->setRotationalVelocity(newRotationVel);
        float newRotationPos = (rotationPosition + newRotationVel * dt.asSeconds());
        smokePointer->setRotationalPosition(newRotationPos);

        // Check if smoke has expired and remove from vector
        if ((*it)->isExpired()) {
            it = m_smokeObjects.erase(it);
        }
        else {
            ++it;
        }

    }


}

void Game::drawGame(sf::RenderWindow& window)
{
    // Clear window before drawing
    window.clear();

    // draw everything here
    //for (auto ball : ballarray)
    //{
    //    if (ball.getradius()) // draw if radius is not zero
    //    {
    //        window.draw(ball.getshape());
    //    }
    //}
        

    //draw convex triangle
    window.draw(m_convexTriangle);


    //Draw smoke (put in func)
    for (auto smoke : m_smokeObjects)
    {
        if (smoke->getRadius()) // Draw if radius is not zero
        {
            window.draw(smoke->getShape());
        }
    }



    //draw sprite
    sf::Sprite testSprite;
    testSprite.setPosition(sf::Vector2f{ 200.0f, 200 });
    testSprite.setTexture(m_smokeTexture);
    sf::Vector2u textureSize = m_smokeTexture.getSize();
    testSprite.setOrigin(textureSize.x/2, textureSize.y/2);
    testSprite.setRotation(90);

    //window.draw(testSprite);


    // Display everything that has been drawn
    window.display();
}

void Game::interact(sf::RenderWindow& window)
{
    bool isLeftMouseButtonPressed = false;
    while (window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (m_event.type == sf::Event::MouseButtonPressed)
        {
            if (m_event.mouseButton.button == sf::Mouse::Left)
            {
                //sf::Vector2i mousePos(m_event.mouseButton.x, m_event.mouseButton.y);
                //sf::Vector2i worldMousePos(window.mapPixelToCoords(mousePos));
                //m_worldMousePos = window.mapPixelToCoords(mousePos);
                isLeftMouseButtonPressed = true;
            }
        }

        if (m_event.type == sf::Event::MouseButtonReleased)
        {
            isLeftMouseButtonPressed = false;
        }


    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Your other actions here
        //sf::Vector2i mousePos(m_event.mouseButton.x, m_event.mouseButton.y);
        //sf::Vector2i worldMousePos(window.mapPixelToCoords(mousePos));
        //m_worldMousePos = window.mapPixelToCoords(mousePos);

            // This code block will execute continuously while the left mouse button is held down
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
        m_worldMousePos = worldMousePos;




        //Generatre a random number (put in func)
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a uniform distribution between -1.0 and 1.0
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        // Generate a random float between -1 and 1
        float randomValue = dist(gen);
        //std::cout << "Random value between -1 and 1: " << randomValue << std::endl;


        //Get angle between convexTriangle and mouse
        float angleRad = std::atan2(m_worldMousePos.y - m_convexTriangle.getPosition().y, m_worldMousePos.x - m_convexTriangle.getPosition().x);
        angleRad = angleRad + (rand() % 20 - 10)*M_PI/180.0f; //randomValue * 5.0f*M_PI/180.0f;

        //from velTotal
        float velTot = 1000;
        velTot = velTot + randomValue * 200.0f; // add noise


        //Create smoke object and put in vector
        Smoke* smokeObject = new Smoke(m_convexTriangle.getPosition(), sf::Vector2f(cosf(angleRad) * velTot, sinf(angleRad) * velTot), 25, sf::Color(255,255,255,100), sf::seconds(8.0f)); // rand() % 50 + 25
        smokeObject->getShapeReference().setTexture(m_smokeTexture);
        sf::Vector2u texture_size = m_smokeTexture.getSize();
        smokeObject->getShapeReference().setOrigin(texture_size.x/2, texture_size.y/2);
        m_smokeObjects.push_back(smokeObject);

    }


    // Get the mouse position
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    m_worldMousePos = mousePosition;
    //std::cout << m_worldMousePos .x << "," << m_worldMousePos.y << std::endl;
}

void Game::updateBallVelAndPos(Smoke& smoke, sf::Time dt)
{
    float vX = smoke.getVel().x;
    float vY = smoke.getVel().y;
    float pX = smoke.getPos().x;
    float pY = smoke.getPos().y;

    //// Update position of balls here.
    //sf::Vector2f newVel(vX - 0 * dt.asSeconds(), vY + 0 * dt.asSeconds());
    //smoke.setVel(newVel);
    //sf::Vector2f newPos(pX + vX * dt.asSeconds() + dt.asSeconds() * dt.asSeconds() * 0 / 2.0f,
    //    pY + vY * dt.asSeconds() + dt.asSeconds() * dt.asSeconds() * 0 / 2.0f);
    //smoke.setPos(newPos);
    //std::cout << smoke.getVel().x << std::endl;
    /////////////////

    //Update position and velocity of objects + friction
    //Add friction
    float friction = 0.97f;
    sf::Vector2f newVel(vX * friction, vY * friction);
    smoke.setVel(newVel);
    sf::Vector2f newPos(pX + vX * dt.asSeconds() + dt.asSeconds() * dt.asSeconds() * 0 / 2.0f,
        pY + vY * dt.asSeconds() + dt.asSeconds() * dt.asSeconds() * 0 / 2.0f);
    smoke.setPos(newPos);
   

}

float Game::clamp(float x, float lowerlimit, float upperlimit)
{
    if (x < lowerlimit) return lowerlimit;
    if (x > upperlimit) return upperlimit;
    return x;
}

float Game::smoothstep(float edge0, float edge1, float x)
{
    // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0));

    return x * x * (3.0f - 2.0f * x);
}

