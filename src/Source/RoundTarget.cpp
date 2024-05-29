#include "RoundTarget.hpp"

RoundTarget::RoundTarget(float radius, sf::Color color, float x, float y)
{
    mShape.setRadius(radius);
    mShape.setFillColor(color);
    mShape.setPosition(x,y);
}

void RoundTarget::drawCurrent(sf::RenderWindow &window) const {
    window.draw(mShape);
}

void RoundTarget::handlePlayerInput(const sf::Keyboard::Key &key, const bool &isPressed) {
    if (key == sf::Keyboard::Z)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void RoundTarget::update(const sf::Time &elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= TargetSpeed;
    if (mIsMovingDown)
        movement.y += TargetSpeed;
    if (mIsMovingLeft)
        movement.x -= TargetSpeed;
    if (mIsMovingRight)
        movement.x += TargetSpeed;

    mShape.move(movement * elapsedTime.asSeconds());

}

