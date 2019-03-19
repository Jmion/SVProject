//
// Created by jeremy on 3/17/19.
//

#include "Animal.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <Application.hpp>
#include <cmath>

double Animal::getMass() const{
    return ANIMAL_MASS;
}

double Animal::getStandardMaxSpeed() const {
    return ANIMAL_MAX_SPEED;
}

Animal& Animal::setTargetPosition(const Vec2d &target) {
    targetPosition = target;
    return *this;
}

Vec2d Animal::getSpeedVector() const {
    return direction*speed;
}

Animal::Animal(const Vec2d &_position, Deceleration _deceleration) :
        CircularCollider(_position, ANIMAL_RADIUS), speed(0), direction(Vec2d(1, 0)), targetPosition(Vec2d(0, 0)),
        deceleration(_deceleration) {}

void Animal::update(sf::Time dt) {
    auto targetList = getAppEnv().getTargetsInSightForAnimal(this);
    Vec2d attraction_force = attractionForce();
    if (targetList.size() > 0) {
        setTargetPosition(*targetList.begin());
        updateMovementVariables(attraction_force, dt);
    }else{

    }

    //TODO do we need to take the closest target?
}


void Animal::draw(sf::RenderTarget &targetWindow) {
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture));
    targetWindow.draw(image_to_draw);
    sf::Color red(255,0,0);
    targetWindow.draw(buildCircle(targetPosition,5,red));
    drawVision(targetWindow);
}

void Animal::drawVision(sf::RenderTarget& target) const {
    sf::Color black = sf::Color::Black;
    black.a = 16; //setting alpha value to 16, light gray transparent
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD*2), getViewDistance(), getPosition(), black, direction.angle()/DEG_TO_RAD));
    target.draw(arc);
}

Vec2d Animal::attractionForce() const {
    Vec2d toTarget = targetPosition - getPosition();
    double speed = fmin(toTarget.length() / getDecelerationRate(), getStandardMaxSpeed());
    Vec2d v_target = toTarget/toTarget.length()*speed;
    return v_target-getSpeedVector();
}

void Animal::updateMovementVariables(const Vec2d& acceleration, const sf::Time dt) {
    Vec2d new_speed = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d new_direction = new_speed.normalised();
    speed = fmin(getStandardMaxSpeed(), new_speed.length());
    //setTargetPosition(targetPosition + new_speed * dt.asSeconds());
    direction = new_direction;
    move(getSpeedVector() * dt.asSeconds());
}

double Animal::getDecelerationRate() const {
    switch (deceleration){
        case WEAK:
            return 0.9;
        case MEDIUM:
            return 0.6;
        default: // STRONG
            return 0.3;
    }
}


double Animal::getViewRange() const{
    return ANIMAL_VIEW_RANGE;
}


double Animal::getViewDistance() const{
    return ANIMAL_VIEW_DISTANCE;
}


Animal& Animal::setRotation(double angle){
    direction = Vec2d(cos(angle), sin(angle));
    return *this;
}


double Animal::getRotation() const{
    return direction.angle();
}

void Animal::setDeleleration(Deceleration decel){
    deceleration = decel;
}

//called very frequently
bool Animal::isTargetInSight(const Vec2d &target) const{
    Vec2d d = target - getPosition();
    if(d.lengthSquared() <= getViewDistance()*getViewDistance()){
        Vec2d this_to_target = target-getPosition();
        double length = this_to_target.lengthSquared();
        if (isEqual(length, 0)) {
            return true;
        }
        this_to_target = this_to_target.normalised();
        return direction.dot(this_to_target) >= cos((getViewRange() + 0.001) / 2);
    }
    return false;
}