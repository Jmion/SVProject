//
// Created by jeremy on 5/4/19.
//

#ifndef PARTIE1_NEURONALSCORPION_HPP
#define PARTIE1_NEURONALSCORPION_HPP

#include <Animal/Scorpion.hpp>
class Sensor;

class NeuronalScorpion  : public Scorpion{
public:

    NeuronalScorpion(const Vec2d &position, double energyLevel, bool isFemale);

    virtual ~NeuronalScorpion();

    explicit NeuronalScorpion(const Vec2d &position);

    Vec2d getPositionOfSensor(const Sensor* s);


private:
    static constexpr int nbSensor = 8;

    std::array<Sensor*,nbSensor> sensor;

    void initializeSensors();


};


#endif //PARTIE1_NEURONALSCORPION_HPP
