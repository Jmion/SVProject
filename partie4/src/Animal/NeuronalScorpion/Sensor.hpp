//
// Created by jeremy on 5/4/19.
//

#ifndef PARTIE1_SENSOR_HPP
#define PARTIE1_SENSOR_HPP

class NeuronalScorpion;

class Sensor : public Updatable
{
private:

    /*!
     * Scorpion that owns this sensor
     */
    NeuronalScorpion* owner;

    /*!
     * Angle from scorpion in radians
     */
    double angleFromScorpion;

    /*!
     * Sensor activated state
     */
    bool actif;

    /*! perception of wave
    * double score;
    */
    double score;

    /*!
     * Sensibility to inhibition signals from neighbours
     */
    double inhibitor;

    std::array<Sensor *, 3> sensorsToInhibit = {nullptr, nullptr, nullptr};

    /*!
     * Intensity of the waves that the sensor is detecting
     * @return
     */
    double getIntensity();

    /*!
     * @return the position of the sensor in world coordinates
     */
    Vec2d getPositionOfSensor();

    /*!
     * Allows change of the inhibitor value within a given range.
     * Cannot set bellow 0, or greater values that what is deffined in the
     * config file.
     *
     * Values outside of this range will be clamped
     * @param inhibitor value wanted to set.
     */
    void setInhibitor(double inhibitor);

    /*!
     * Inhibits this sensor by the score of another sensor
     * @param score of other sensor inhibiting this
     */
    void inhibit(double score);

public:

    /*!
     * @return true is sensor is active
     */
    bool isActif() const;

    Sensor(double angleFromScorpion, NeuronalScorpion* neuronalScorpion);

    /*!
     * Gets from config file distance from sensor to scorpion.
     * @return radius from scorpion
     */
    double radiusFromScorpion() const;

    /*!
     * Getter for angle relative to scorpion
     * @return
     */
    double getAngle() const;

    /*!
     * Allows the configuration of which sensors are to be inhibited by this
     * @param sensorsToInhibit list of sensors to inhibit.
     */
    void setInhibitSensor(std::array<Sensor *,3> sensorsToInhibit);

    /*!
     * @return score of the sensor
     */
    double getScore() const;

    /*!
     * @return inhibitor value
     */
    double getInhibitor() const;

    /*!
     * resets the sensors score and inhibition value to zero
     */
    void resetSensor();

    void update(sf::Time dt) override;
};


#endif //PARTIE1_SENSOR_HPP
