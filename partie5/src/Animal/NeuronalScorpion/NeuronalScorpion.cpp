//
// Created by jeremy on 5/4/19.
//

#include <Application.hpp>
#include "NeuronalScorpion.hpp"
#include "Sensor.hpp"
#include <cmath>

NeuronalScorpion::NeuronalScorpion(const Vec2d &position, double energyLevel, bool isFemale) : Scorpion(position,
                                                                                                        energyLevel,
                                                                                                        isFemale),
                                                                                                        stateTimer(sf::Time::Zero),
                                                                                                        state(NeuronalScorpion::State::WANDERING),
                                                                                                        sensorActifTimer(sf::Time::Zero)
                                                                                                        {
    initializeSensors();
}

NeuronalScorpion::NeuronalScorpion(const Vec2d &position) : Scorpion(position),
                                                            stateTimer(sf::Time::Zero),
                                                            state(NeuronalScorpion::State::WANDERING),
                                                            sensorActifTimer(sf::Time::Zero) {
    initializeSensors();
}

Vec2d NeuronalScorpion::getPositionOfSensor(const Sensor* s) const {
    if(s!= nullptr){
        double distanceSensorFromScorpion = s->radiusFromScorpion();
        double radAngle = s->getAngle();
        Vec2d localPositionOfSensor = Vec2d(cos(radAngle), sin(radAngle))*distanceSensorFromScorpion;
        return convertToGlobalCoord(localPositionOfSensor);
    }
    else{
        throw std::invalid_argument("Null pointer in NeuronalScorpion:getPositionOfSensor");
    }
}

void NeuronalScorpion::initializeSensors() {
    int sensorAngles[nbSensor] = {18, 54, 90, 140, -140, -90, -54, -18};
    for (int i = 0; i < nbSensor; ++i) {
        sensor[i] = new Sensor(sensorAngles[i]*DEG_TO_RAD,this);
    }
    for (int j = 0; j < nbSensor; ++j) {
        std::array<Sensor*, 3> inhibitSensors = {nullptr, nullptr, nullptr};
        for (int i = 3; i <= 5; i++) {
            inhibitSensors.at(i-3) = sensor.at((j+i) % nbSensor);
        }
        sensor.at(j)->setInhibitSensor(inhibitSensors);
    }

}

NeuronalScorpion::~NeuronalScorpion() {
    for (auto &s : sensor) {
        if (s != nullptr) {
            delete (s);
            s = nullptr;
        }
    }

}


void NeuronalScorpion::update(sf::Time dt) {
    //Animal::update(dt);

    bool sensorActive = false;
    for (auto &s : sensor) {
        s->update(dt);
        if(s->isActif()) {
            sensorActive = true;
        }
    }
    if (sensorActive) {
        sensorActifTimer += dt;
    }

    bool resetSensors = sensorActifTimer.asSeconds() >= getAppConfig().sensor_activation_duration;
    if (resetSensors) {
        estimateDirection = estimateDirectionCalculation();
        this->resetSensors();
        sensorActifTimer = sf::Time::Zero;
    }



    bool hasTarget = false;
    Vec2d attraction_force = Vec2d(0, 0);
    switch (state){
        case WANDERING:
            hasTarget = false;
            attraction_force = randomWalk();
            break;
        case TARGET_IN_SIGHT:
            hasTarget = true;
            attraction_force = attractionForce();
            break;
        case MOVING:
            stateTimer += dt;
            if(fabs(estimateDirection.angle()-getRotation()) > getAppConfig().scorpion_rotation_angle_precision) {
                setRotation(estimateDirection.angle());
                attraction_force = stoppingAttractionForce();
            }else{
                setTargetPosition(convertToGlobalCoord(Vec2d(getAppConfig().simulation_world_size/26,0)));
            }
            break;
        case IDLE:
            stateTimer += dt;
            attraction_force = Vec2d(0, 0);
            break;
    }

    updateState(sensorActive);

    updateMovementVariables(attraction_force, dt, hasTarget);
    OrganicEntity::update(dt);

}

void NeuronalScorpion::resetSensors() const {
    for (auto &s : sensor) {
        s->resetSensor();
    }
}

void NeuronalScorpion::updateState(bool sensorActif) {
    std::array<OrganicEntity *, 3> closestEnities = analyseEnvironment();

    if(closestEnities.at(0) != nullptr){
        NeuronalScorpion::state = TARGET_IN_SIGHT;
        targetPosition = closestEnities.at(0)->getPosition();
        if (isColliding(*closestEnities.at(0))) {
            eat(closestEnities.at(0));
        }
    }else{
        switch (state) {
            case TARGET_IN_SIGHT:
                stateTimer = sf::Time::Zero;
                state = IDLE;
                break;
            case MOVING:
                if (stateTimer.asSeconds() >= MAX_WAIT_IN_MOVING) {
                    stateTimer = sf::Time::Zero;
                    state = IDLE;
                    estimateDirection = Vec2d(0, 0);
                }
                break;
            case WANDERING:
                if(sensorActif) {
                    stateTimer = sf::Time::Zero;
                    state = IDLE;
                }
                break;
            case IDLE:
                if (scoreEstimation() >= getAppConfig().scorpion_minimal_score_for_action) {
                    state = MOVING;
                    stateTimer = sf::Time::Zero;
                } else if (stateTimer.asSeconds() >= MAX_WAIT_IN_IDLE) {
                    stateTimer = sf::Time::Zero;
                    state = WANDERING;

                }
                break;
        }
    }
}

Vec2d NeuronalScorpion::estimateDirectionCalculation() const {
    Vec2d direction(0, 0);
    double theta = getRotation();
    for (auto &s : sensor) {
        double alpha = s->getAngle();
        direction += (s->radiusFromScorpion() * Vec2d(cos(alpha + theta), sin(alpha + theta))) * s->getScore();
    }
    return direction;
}

double NeuronalScorpion::scoreEstimation() {
    return estimateDirection.length();
}

const Vec2d &NeuronalScorpion::getTargetPosition() const {
    return targetPosition;
}

void NeuronalScorpion::draw(sf::RenderTarget &targetWindow) const {
    Animal::draw(targetWindow);
    if (isDebugOn()) {
        for (auto &s: sensor) {
            sf::Color c = sf::Color::Black;
            if (s->isActif()) {
                if (s->getInhibitor() > 0.2) {
                    c = sf::Color::Magenta;
                }else{
                    c = sf::Color::Red;
                }
            }else{
                if (s->getInhibitor() > 0.2) {
                    c = sf::Color::Blue;
                }else{
                    c = sf::Color::Green;
                }
            }

            //draw the direction
            sf::RectangleShape scorpion_dir(sf::Vector2f(100, 2));
            scorpion_dir.setFillColor(sf::Color::Red);
            scorpion_dir.rotate(getRotation()/DEG_TO_RAD);
            scorpion_dir.setPosition(getPosition());
            targetWindow.draw(scorpion_dir);

            //draw the estimated target
            sf::RectangleShape line(sf::Vector2f(100, 2));
            line.setFillColor(sf::Color::Blue);
            line.rotate(estimateDirection.angle()/DEG_TO_RAD);
            line.setPosition(getPosition());
            targetWindow.draw(line);

            targetWindow.draw(buildCircle(getPositionOfSensor(s),getRadius()/5, c));
        }
    }

    auto text = buildText("State time " + to_nice_string(stateTimer.asSeconds()) + "\nSensorActifTimer :" +
                          to_nice_string(sensorActifTimer.asSeconds()) + "\nState: " + to_nice_string(state),
                          convertToGlobalCoord(Vec2d(140, 0)), getAppFont(),
                          getAppConfig().default_debug_text_size,
                          sf::Color::Black, getRotation() / DEG_TO_RAD + 90);
    targetWindow.draw(text);

}

std::string NeuronalScorpion::getStateString() const {
    return ToString(state);
}

double NeuronalScorpion::getMaxSpeed() const {
    if (getEnergyLevel() < getStarvingEnergyLevel())
        return getStandardMaxSpeed() * getAppConfig().animal_starving_speed_factor;
    switch (state) {
        case TARGET_IN_SIGHT:
            return getStandardMaxSpeed() * 3;
        default:
            return getStandardMaxSpeed();
    }
}


