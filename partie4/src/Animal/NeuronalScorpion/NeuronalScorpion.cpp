//
// Created by jeremy on 5/4/19.
//

#include "NeuronalScorpion.hpp"
#include "Sensor.hpp"

NeuronalScorpion::NeuronalScorpion(const Vec2d &position, double energyLevel, bool isFemale) : Scorpion(position,
                                                                                                        energyLevel,
                                                                                                        isFemale) {
    initializeSensors();

}

NeuronalScorpion::NeuronalScorpion(const Vec2d &position) : Scorpion(position) {
    initializeSensors();
}



Vec2d NeuronalScorpion::getPositionOfSensor(const Sensor* s) {
    if(s!= nullptr){
        double distanceSensorFromScorpion = s->radiusFromScorpion();
        double radAngle = s->getAngle() * DEG_TO_RAD;
        Vec2d localPositionOfSensor = Vec2d(cos(radAngle), sin(radAngle))*distanceSensorFromScorpion + getPosition();
        return convertToGlobalCoord(localPositionOfSensor);
    }
    else{
        throw std::invalid_argument("Null pointer in NeuronalScorpion:getPositionOfSensor");
        return Vec2d();
    }
}

void NeuronalScorpion::initializeSensors() {
    int sensorAngles[nbSensor] = {18, 54, 90, 140, -140, -90, -54, -18};
    for (int i = 0; i < nbSensor; ++i) {
        sensor[i] = new Sensor(sensorAngles[i],this);
    }
    for (int j = 0; j < nbSensor; ++j) {
        std::array<Sensor*, 3> inhibitSensors = {nullptr, nullptr, nullptr};
        for (int i = 3; i <= 5; i++) {
            inhibitSensors.at(i-3) = sensor.at((j+i-3) % nbSensor);
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
