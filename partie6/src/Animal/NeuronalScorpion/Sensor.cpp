//
// Created by jeremy on 5/4/19.
//

#include <Application.hpp>
#include "Sensor.hpp"
#include <cmath>
#include "NeuronalScorpion.hpp"
#include <Environment/Wave.hpp>
#include <Utility/Macros.hpp>

double Sensor::radiusFromScorpion() const{
    return getAppConfig().scorpion_sensor_radius;
}

Sensor::Sensor(double angleFromScorpion, NeuronalScorpion* neuronalScorpion) :
owner(neuronalScorpion),
angleFromScorpion(angleFromScorpion),
actif(false),
score(0),
inhibitor(0){
    if (neuronalScorpion == nullptr) {
        throw std::invalid_argument("neuronalScorpion of class Sensor is nullptr.");
    }
}

double Sensor::getAngle() const {
    return angleFromScorpion;
}

void Sensor::setInhibitor(double inhibitor) {
    this->inhibitor = fmax(0, fmin(getAppConfig().sensor_inhibition_max, inhibitor));
}

void Sensor::update(sf::Time A_Unused dt) {
    if (actif) {
        score += 2.0 * (1.0 - inhibitor);
        for (auto &s : sensorsToInhibit) {
            s->inhibit(score);
        }
    }else if(getIntensity() >= getAppConfig().sensor_intensity_threshold){
        actif = true;
    }
}

double Sensor::getIntensity() {
    double intensity(0);
    Vec2d positionOfSensor = getPositionOfSensor();
    std::list<Wave*> collidingWaves = getAppEnv().getWaveCollidingWithSensor(positionOfSensor);
    for (auto &w: collidingWaves) {
        if(w->isPointWithinArcs(positionOfSensor))
            intensity += w->getIntensity();
    }
    return intensity;
}

Vec2d Sensor::getPositionOfSensor() {
    return owner->getPositionOfSensor(this);
}

void Sensor:: resetSensor() {
    inhibitor = 0;
    score = 0;
    actif = false;
}

void Sensor::setInhibitSensor(std::array<Sensor *, 3> sensorsToInhibit) {
    this->sensorsToInhibit = sensorsToInhibit;
}

void Sensor::inhibit(double score) {
    setInhibitor(inhibitor + score * getAppConfig().sensor_inhibition_factor);
}

bool Sensor::isActif() const {
    return actif;
}

double Sensor::getScore() const {
    return score;
}

double Sensor::getInhibitor() const {
    return inhibitor;
}


