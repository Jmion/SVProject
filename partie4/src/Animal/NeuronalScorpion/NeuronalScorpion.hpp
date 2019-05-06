//
// Created by jeremy on 5/4/19.
//

#ifndef PARTIE1_NEURONALSCORPION_HPP
#define PARTIE1_NEURONALSCORPION_HPP

#include <Animal/Scorpion.hpp>
#include <Utility/Macros.hpp>
class Sensor;

class NeuronalScorpion  : public Scorpion{
public:

    DEFINE_ENUM_WITH_STRING_CONVERSIONS(State,(IDLE)(WANDERING)(TARGET_IN_SIGHT)(MOVING))



    static constexpr int MAX_WAIT_IN_IDLE = 5;
    static constexpr int MAX_WAIT_IN_MOVING = 3;

    NeuronalScorpion(const Vec2d &position, double energyLevel, bool isFemale);

    virtual ~NeuronalScorpion();

    void draw(sf::RenderTarget &targetWindow) const override;

    explicit NeuronalScorpion(const Vec2d &position);

    Vec2d getPositionOfSensor(const Sensor* s) const;

    const Vec2d &getTargetPosition() const override;


protected:

    std::string getStateString() const override;


private:
    static constexpr int nbSensor = 8;

    std::array<Sensor*,nbSensor> sensor;

    void initializeSensors();

    /*!
     * Time that current state has spend.
     */
    sf::Time stateTimer;

    State state;

    /*!
     * Time that sensors have been active
     */
    sf::Time sensorActifTimer;

    /*!
     * Target of the current animal
     */
    Vec2d targetPosition;

    /*!
     * estimate direction
     */
    Vec2d estimateDirection;

private:

    /*!
     * Sets current state to state and resets timer
     */
    void setState(State state1);

    /*!
     * Updates the state of the animal
     * @param dt time since last update
     * @param sensorActif true is a sensor is actif
     */
    void updateState(sf::Time dt, bool sensorActif);

    /*!
     * Estimate direction of target using sensor information.
     * @return
     */
    Vec2d estimateDirectionCalculation() const;

    /*!
     * Estiamte score of the sensors of this animal
     * @param estimateDirection optional parameter. estimateDirection is used to calculate teh estimate score
     * @return estimate score
     */
    double scoreEstimation();



public:
    void update(sf::Time dt) override;

    /*!
     * Resets all the sensors to default config.
     */
    void resetSensors() const;
};


#endif //PARTIE1_NEURONALSCORPION_HPP
