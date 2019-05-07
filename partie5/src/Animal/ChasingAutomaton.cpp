//
// Created by jeremy on 3/17/19.
//

#include "ChasingAutomaton.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <Application.hpp>
#include <cmath>

double ChasingAutomaton::getMass() const
{
    return CHASING_AUTOMATON_MASS;
}

double ChasingAutomaton::getStandardMaxSpeed() const
{
    return CHASING_AUTOMATON_MAX_SPEED;
}

ChasingAutomaton& ChasingAutomaton::setTargetPosition(const Vec2d &target)
{
    targetPosition = target;
    return *this;
}

Vec2d ChasingAutomaton::getSpeedVector() const
{
    return direction*speed;
}

ChasingAutomaton::ChasingAutomaton(const Vec2d &_position, Deceleration _deceleration) :
    CircularCollider(_position, CHASING_AUTOMATON_RADIUS), speed(0), direction(Vec2d(1, 0)),
    targetPosition(Vec2d(0, 0)), deceleration(_deceleration) {}

void ChasingAutomaton::update(sf::Time dt)
{
    updateMovementVariables(attractionForce(), dt);
}


void ChasingAutomaton::draw(sf::RenderTarget &targetWindow)
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture));
    targetWindow.draw(image_to_draw);
    //sf::Color red(255,0,0);
    //targetWindow.draw(buildCircle(targetPosition,5,red));
}

Vec2d ChasingAutomaton::attractionForce() const
{
    Vec2d toTarget = targetPosition - getPosition();
    double speed = fmin(toTarget.length() / getDecelerationRate(), getStandardMaxSpeed());
    Vec2d v_target = toTarget/toTarget.length()*speed;
    return v_target-getSpeedVector();
}

void ChasingAutomaton::updateMovementVariables(const Vec2d& acceleration, const sf::Time dt)
{
    Vec2d new_speed = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d new_direction = new_speed.normalised();
    speed = fmin(getStandardMaxSpeed(), new_speed.length());
    //setTargetPosition(targetPosition + new_speed * dt.asSeconds());
    direction = new_direction;
    move(getSpeedVector() * dt.asSeconds());
}

double ChasingAutomaton::getDecelerationRate() const
{
    switch (deceleration) {
    case WEAK:
        return 0.9;
    case MEDIUM:
        return 0.6;
    default: // STRONG
        return 0.3;

    }
}

void ChasingAutomaton::setDeleleration(Deceleration decel)
{
    deceleration = decel;
}