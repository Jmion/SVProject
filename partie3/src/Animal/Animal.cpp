//
// Created by jeremy on 3/17/19.
//

#include "Animal.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <Application.hpp>
#include <cmath>
#include <Random/Uniform.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Utility/Macros.hpp>
#include <array>



Animal::Animal(const Vec2d& _position, double size, double energyLevel, bool isFemale, Deceleration _deceleration):
        OrganicEntity(_position, size, energyLevel),
        speed(0),
        hasTarget(false),
        direction(Vec2d(1, 0)),
        current_target(Vec2d(1, 0)),
        targetPosition(Vec2d(0, 0)),
        isFemale(isFemale),
        isPregnant(false),
        numberOfChildren(0),
        deceleration(_deceleration),
        state(WANDERING),
        mattingWaitTime(sf::Time::Zero),
        gestationTime(sf::Time::Zero),
        givingBirthTime(sf::Time::Zero),
        predatorPosition(){}

Animal& Animal::setTargetPosition(const Vec2d &target)
{
    targetPosition = target;
    return *this;
}

Vec2d Animal::getSpeedVector() const
{
    return direction*speed;
}

void Animal::draw(sf::RenderTarget &targetWindow) const
{
    CircularCollider::draw(targetWindow);
    sf::Texture& texture = getAppTexture(getTexturePath());
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture, getRotation()/DEG_TO_RAD));
    targetWindow.draw(image_to_draw);
    if(isDebugOn()) {
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
        if(getIsPregnant()){
            targetWindow.draw(buildAnnulus(getPosition(), getRadius(), sf::Color::Magenta,4 ));
        }

        //textual details about the animal
        std::string stateString = ToString(state);
        std::string sexString = isFemale?"Female":"Male";
        auto text = buildText("State: " + stateString  + " \nenergy level: " +
                              to_nice_string(getEnergyLevel())+"\nage:" + to_nice_string(getAge().asSeconds()) +
                              "\ngivingBirth:"+to_nice_string(givingBirthTime.asSeconds())+
                              "\n"+sexString+
                              "\nnumber of children:"+to_nice_string(getNumberOfChildren())+
                              "\nenergy:"+to_nice_string(getEnergyLevel()),
                              convertToGlobalCoord(Vec2d(-100, 0)), getAppFont(), getAppConfig().default_debug_text_size,
                              sf::Color::Black, getRotation() / DEG_TO_RAD + 90);
        targetWindow.draw(text);
    }
}

void Animal::drawVision(sf::RenderTarget& target) const
{
    sf::Color black = sf::Color::Black;
    black.a = 16; //setting alpha value to 16, light gray transparent
    Arc arc(buildArc(-getViewRange()/(DEG_TO_RAD*2), getViewRange()/(DEG_TO_RAD*2), getViewDistance(), getPosition(), black, direction.angle()/DEG_TO_RAD));
    target.draw(arc);
}


void Animal::update(sf::Time dt)
{
    OrganicEntity::update(dt);
    updateState(dt);

    Vec2d attraction_force = Vec2d(0, 0);
    switch(state) {
        case WANDERING:
            hasTarget=false;
            attraction_force = randomWalk();
            break;
        case FOOD_IN_SIGHT:
            hasTarget = true;
            attraction_force = attractionForce();
            break;
        case FEEDING:
            break;
        case DIESTING:
            hasTarget = true;
            attraction_force = stoppingAttractionForce();
            break;
        case MATE_IN_SIGHT:
            hasTarget = true;
            attraction_force = attractionForce();
            break;
        case MATING:
            hasTarget = true;
            attraction_force = stoppingAttractionForce();
           break;
        case GIVING_BIRTH:
            hasTarget = true;
            giveBirth();
            attraction_force = stoppingAttractionForce();
            break;
        case RUNNING_AWAY:
            attraction_force = runningAwayForce();
            break;
        default:
            attraction_force = Vec2d(0, 0);
    }

    updateMovementVariables(attraction_force, dt);

    //aging(dt);
    spendEnergy(dt);
}

void Animal::updateState(sf::Time dt)
{
    std::array<OrganicEntity *,3> closestEntities = analyseEnvironment();

    bool feedingHasWaitedLongEnough = updateAndHasWaitedLongEnoughFeeding(dt);
    bool mattingHasWaitedLongEnough = updateAndHasWaitedLongEnoughMatting(dt);
    bool gestationWaitedLongEnough = updateAndHasWaitedLongEnoughGestationTime(dt);
    bool givingBirthWaitedLongEnough = updateAndHasWaitedLongEnoughGivingBirthTime(dt);

    if(!predatorPosition.empty()){
        state = RUNNING_AWAY;
    }
    else if(!feedingHasWaitedLongEnough) {
        state = DIESTING;
    }else if(state == MATING){
        if(mattingHasWaitedLongEnough){
            state = WANDERING;
            mattingWaitTime = sf::Time::Zero;
        }
    }else if(gestationWaitedLongEnough && getIsFemale()){
        state = GIVING_BIRTH;
        if(givingBirthWaitedLongEnough){
            state = WANDERING;
            gestationTime = sf::Time::Zero;
        }
    }
    else if(closestEntities.at(1) != nullptr && matable(closestEntities.at(1)) && closestEntities.at(1)->matable(this)) {
        if (isColliding(*closestEntities.at(1)) && state == MATE_IN_SIGHT) {
            meet(closestEntities.at(1));
        }else {
            state = MATE_IN_SIGHT;
        }
        if(closestEntities.at(1) != nullptr) {
            targetPosition = closestEntities.at(1)->getPosition();
        }
    }
    else {
        state = WANDERING;
        givingBirthTime= sf::Time::Zero;
        //FOOD

        if (closestEntities.at(0) != nullptr && eatable(closestEntities.at(0))) {
            state = FOOD_IN_SIGHT;
            if (isColliding(*closestEntities.at(0))) {
                state = FEEDING;
                eat(closestEntities.at(0));
            }
        }
        if (closestEntities.at(0) != nullptr) {
            targetPosition = closestEntities.at(0)->getPosition();
        }

    }
}

std::array<OrganicEntity *,3> Animal::analyseEnvironment() {
    std::list<OrganicEntity *> entities = getAppEnv().getEntitiesInSightForAnimal(this);


    std::array<OrganicEntity *, 3> closestEntities {nullptr, nullptr, nullptr};
    for (auto e: entities) {
            if (eatable(e)) {
                if (closestEntities.at(0) == nullptr) {
                    closestEntities.at(0) = e;
                } else if (distanceTo(e->getPosition()) < distanceTo(closestEntities.at(0)->getPosition())) {
                        closestEntities.at(0) = e;

                }
            }
            if(matable(e)){
                if (closestEntities.at(1) == nullptr) {
                    closestEntities.at(1) = e;
                } else if (distanceTo(e->getPosition()) < distanceTo(closestEntities.at(1)->getPosition())) {
                    closestEntities.at(1) = e;
                }
            }
            if(e->eatable(this)){
                predatorPosition.push_back(e->getPosition());
            }
        }
    return closestEntities;
}

Vec2d Animal::attractionForce() const
{
    Vec2d toTarget = targetPosition - getPosition();
    double speed = fmin(toTarget.length() / getDecelerationRate(), getMaxSpeed());
    Vec2d v_target = toTarget/toTarget.length()*speed;
    return v_target-getSpeedVector();
}

void Animal::updateMovementVariables(const Vec2d& acceleration, const sf::Time &dt)
{
    Vec2d new_speed = getSpeedVector() + acceleration * dt.asSeconds();
    Vec2d new_direction = new_speed.normalised();
    speed = fmin(getMaxSpeed(), new_speed.length());
    direction = new_direction;
    move(getSpeedVector() * dt.asSeconds());
}

double Animal::getDecelerationRate() const
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


Animal& Animal::setRotation(double angle)
{
    direction = Vec2d(cos(angle), sin(angle));
    return *this;
}


double Animal::getRotation() const
{
    return direction.angle();
}

void Animal::setDeleleration(Deceleration decel)
{
    deceleration = decel;
}

//called very frequently
bool Animal::isTargetInSight(const Vec2d &target) const
{
    Vec2d d = target - getPosition();
    if(d.lengthSquared() <= getViewDistance()*getViewDistance()) {
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

Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised();
    current_target *= getRandomWalkRadius();
    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
    return convertToGlobalCoord(moved_current_target) - getPosition();
}


Vec2d Animal::convertToGlobalCoord(const Vec2d& v) const
{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate(direction.angle() / DEG_TO_RAD);
    return matTransform.transformPoint(v);
}

bool Animal::getIsFemale() const
{
    return isFemale;
}

double Animal::getMaxSpeed() const
{
    if(getEnergyLevel()<getStarvingEnergyLevel())
        return getStandardMaxSpeed()*getAppConfig().animal_starving_speed_factor;
    switch (state) {
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

void Animal::spendEnergy(sf::Time dt)
{
    OrganicEntity::spendEnergy(getAppConfig().animal_base_energy_consumption + speed * getEnergyLossFactor() * dt.asSeconds());
}

Vec2d Animal::stoppingAttractionForce()
{
    if(speed <0.04)
        return Vec2d(0, 0);
    setTargetPosition(convertToGlobalCoord(Vec2d(-1,0)));
    return attractionForce();
}

bool Animal::getIsPregnant() const {
    return isPregnant && getIsFemale();
}

bool Animal::canMate(Animal const *partner) const {
    return (getIsFemale() != partner->getIsFemale())
    && !partner->getIsPregnant()
    && partner->state!=GIVING_BIRTH
    && partner->state!=MATING
    && (isFemale?getMinimumMatingEnergyFemale():getMinimumMatingEnergyMale())<=getEnergyLevel()
    && getAge().asSeconds() >= getMinimumMatingAge();
}

int Animal::getNumberOfChildren() const {
    if(isFemale){
        return numberOfChildren;
    }
    return 0;
}

void Animal::procreate() {
    state = MATING;
    if(getIsFemale()){
        hasTarget=true;
        mattingWaitTime = sf::Time::Zero;
        numberOfChildren = uniform(getMinimumNumberOfChildren(),getMaximumNumberOfChildren());
        double energyLost = getEnergyLossFemalePerChild() * numberOfChildren;
        OrganicEntity::spendEnergy(energyLost);
        gestationTime = sf::Time::Zero;
        isPregnant = true;
    }else{
        OrganicEntity::spendEnergy(getEnergyLossMaleMatting());
    }

}

bool Animal::updateAndHasWaitedLongEnoughMatting(sf::Time dt) {
    if(state == MATING)
        mattingWaitTime += dt;
    return mattingWaitTime.asSeconds() >= getAppConfig().animal_mating_time;
}

bool Animal::updateAndHasWaitedLongEnoughGestationTime(sf::Time dt) {
    if(getIsPregnant())
        gestationTime += dt;
    return gestationTime.asSeconds() >= getGestationTimeConfig();
}

bool Animal::giveBirth() {
    if(isPregnant && isFemale){
        isPregnant = false;
        return true;
    }
    return false;
}

bool Animal::updateAndHasWaitedLongEnoughGivingBirthTime(sf::Time dt) {
    if(state == GIVING_BIRTH)
        givingBirthTime += dt;
    return givingBirthTime.asSeconds() >  (getIsFemale()?getAppConfig().animal_delivery_time:0);
}

Vec2d Animal::runningAwayForce() {
    Vec2d force(0,0);
    std::list<Vec2d> toDelete;
    for (auto &it : predatorPosition) {
        Vec2d dir = it -getPosition();
        if(dir.length() > getAppConfig().simulation_world_size/1.4)
            toDelete.push_back(it);
        else
            force -= getAppConfig().animal_running_away_amplification_factor*(dir)/pow(dir.length(),getAppConfig().animal_running_away_distance_ratio);
    }
    for (auto &d : toDelete) {
        predatorPosition.remove(d);
    }

    return force;
}




