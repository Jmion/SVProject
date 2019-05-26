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

    /*!
     * Builds a neuronal scorpion
     * @param position where the scorpion is born
     * @param energyLevel at time 0
     * @param isFemale true if it is female
     */
    NeuronalScorpion(const Vec2d &position, double energyLevel, bool isFemale);

    /*!
     * Destrucor in charge of freeing up scorpion and sensors
     */
    ~NeuronalScorpion() override ;

    /*!
     * Avoid deep copy of neuronalScorpion and sensor. Costly and has no purpose.
     */
    NeuronalScorpion(NeuronalScorpion const& other) = delete;

    void draw(sf::RenderTarget &targetWindow) const override;

    /*!
     * Build a neuronal scorpion specifiying it's position
     * @param position of the neuronal scorpion
     */
    explicit NeuronalScorpion(const Vec2d &position);

    /*!
     * Calculation of the position of the sensors
     * @param s the sensor that we want to know the position of.
     * @return position of the sensor
     */
    Vec2d getPositionOfSensor(const Sensor* s) const;

    const Vec2d &getTargetPosition() const override;

    void update(sf::Time dt) override;

    /*!
     * Resets all the sensors to default config.
     */
    void resetSensors() const;


protected:

    std::string getStateString() const override;

    double getMaxSpeed() const override;

private:
    static constexpr int nbSensor = 8;

    /*!
     * Array of sensors that the scorpion has. A scorpion is in charge of freeing memory
     * when scorpion is destroyed.
     */
    std::array<Sensor*,nbSensor> sensor;

    /*!
     * To be called during constructor. Will initialize the list of sensors.
     * This method will take care of giving to each sensor a list of sensors that it
     * needs to inhibit.
     */
    void initializeSensors();

    /*!
     * Time that current state has spend.
     */
    sf::Time stateTimer;

    /*!
     * State the the scorpion is in.
     */
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

    /*!
     * Updates the state of the animal
     * @param dt time since last update
     * @param sensorActif true is a sensor is actif
     */
    void updateState(bool sensorActif);

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

};


#endif //PARTIE1_NEURONALSCORPION_HPP
