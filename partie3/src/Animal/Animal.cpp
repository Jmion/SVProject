//
// Created by jeremy on 3/17/19.
//

#include "Animal.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <Application.hpp>
#include <cmath>
#include <Random/Uniform.hpp>
#include <Environment/OrganicEntity.hpp>

Animal& Animal::setTargetPosition(const Vec2d &target) {
    targetPosition = target;
    return *this;
}

Vec2d Animal::getSpeedVector() const {
    return direction*speed;
}

Animal::Animal(const Vec2d& _position, double size, double energyLevel, bool isFemale, Deceleration _deceleration):
        OrganicEntity(_position, size, energyLevel),
        speed(0), direction(Vec2d(1, 0)),
        current_target(Vec2d(1, 0)),
        targetPosition(Vec2d(0, 0)),
        isFemale(isFemale),
        deceleration(_deceleration) {

}

void Animal::draw(sf::RenderTarget &targetWindow) const{
    sf::Texture& texture = getAppTexture(getTexturePath());
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture, getRotation()/DEG_TO_RAD));
    targetWindow.draw(image_to_draw);
    sf::Color red(255,0,0);
    targetWindow.draw(buildCircle(targetPosition,5,sf::Color::Red));
    if(isDebugOn()){
        drawVision(targetWindow);
        //Visuallization virtual target
        if(!hasTarget) {
            sf::Color yellow(255, 150, 0);
            targetWindow.draw(
                    buildAnnulus(convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)), getRandomWalkRadius(),
                                 yellow, 2));
            targetWindow.draw(buildCircle(convertToGlobalCoord(current_target + Vec2d(getRandomWalkDistance(), 0)), 5,
                                          sf::Color::Blue));
        }

        auto text = buildText("State: " + getStateString() + " \nenergy level: " + to_nice_string(getEngeryLevel())+"",
                              convertToGlobalCoord(Vec2d(1, 0)), getAppFont(), getAppConfig().default_debug_text_size,
                              sf::Color::Black, getRotation() / DEG_TO_RAD + 90);
    }
}

void Animal::drawVision(sf::RenderTarget& target) const {
    sf::Color black = sf::Color::Black;
    black.a = 16; //setting alpha value to 16, light gray transparent
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD*2), getViewDistance(), getPosition(), black, direction.angle()/DEG_TO_RAD));
    target.draw(arc);
}


void Animal::update(sf::Time dt) {
    updateState(dt);

    //auto targetList = getAppEnv().getEntitiesInSightForAnimal(this);
    Vec2d attraction_force = Vec2d(0, 0);
    switch(state) {
        case WANDERING:
            std::cout << "wandering" << std::endl;
            hasTarget=false;
            attraction_force = randomWalk();
            break;
        case FOOD_IN_SIGHT:
            std::cout<<"FOOD!!!" <<std::endl;
            hasTarget = true;
            attraction_force = attractionForce();
            break;
        default:
            attraction_force = Vec2d(0, 0);
    }

    /*if (!targetList.empty()) {
        setTargetPosition(*targetList.begin());
        hasTarget = true;
    }else{
        attraction_force = randomWalk();
        hasTarget = false;
    }*/
    updateMovementVariables(attraction_force, dt);

    //TODO do we need to take the closest target?
}

void Animal::updateState(sf::Time dt) {
    std::list<OrganicEntity*> entities = getAppEnv().getEntitiesInSightForAnimal(this);

    //default behaviour if nothing in sight
    state = WANDERING;

    OrganicEntity* closestEntity = nullptr;
    for(auto e: entities){
        if (eatable(e)) {
            if (closestEntity == nullptr) {
                closestEntity = e;
            } else {
                if (distanceTo(e->getPosition()) < distanceTo(closestEntity->getPosition())) {
                    closestEntity = e;
                }
            }
            state = FOOD_IN_SIGHT;
        }
    }
    if(closestEntity != nullptr){
        targetPosition = closestEntity->getPosition();
    }
}

Vec2d Animal::attractionForce() const {
    Vec2d toTarget = targetPosition - getPosition();
    double speed = fmin(toTarget.length() / getDecelerationRate(), getMaxSpeed());
    Vec2d v_target = toTarget/toTarget.length()*speed;
    return v_target-getSpeedVector();
}

void Animal::updateMovementVariables(const Vec2d& acceleration, const sf::Time dt) {
    Vec2d new_speed = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d new_direction = new_speed.normalised();
    speed = fmin(getMaxSpeed(), new_speed.length());
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

Vec2d Animal::randomWalk() {
    Vec2d random_vec(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised();
    current_target *= getRandomWalkRadius();
    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
    return convertToGlobalCoord(moved_current_target) - getPosition();
}


Vec2d Animal::convertToGlobalCoord(const Vec2d& v) const{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate(direction.angle() / DEG_TO_RAD);
    return matTransform.transformPoint(v);
}

bool Animal::getIsFemale() const {
    return isFemale;
}

double Animal::getMaxSpeed() const {
    switch (state){
        case FOOD_IN_SIGHT:
            return getStandardMaxSpeed() * 3;
        case MATE_IN_SIGHT:
            return getStandardMaxSpeed() * 2;
        case RUNNING_AWAY:
            return getStandardMaxSpeed() * 4;
        default:
            return getStandardMaxSpeed();
    }
}


