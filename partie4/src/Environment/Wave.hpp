//
// Created by jeremy on 4/30/19.
//

#ifndef PARTIE1_WAVE_HPP
#define PARTIE1_WAVE_HPP


#include <Utility/Vec2d.hpp>
#include <Obstacle/CircularCollider.hpp>
#include <Utility/Arc.hpp>
#include <list>


class Wave : public CircularCollider, public Updatable {

private:

    /*!
     * Arcs than compose the wave
     */
    std::list<std::pair<double,double>> arcs;


    /*!
     * Initial amount of energy that the wve has
     */
    double  initialEnergy;

    /*!
     * ratio de perte d'energie par rapport au temps
     */
    const double mu;

    /*!
     * Speed of propagation of the wave
     */
    double speed;

public:
    Wave(const Vec2d &position, double initialEnergy, double radius, double mu,double speed);
    ~Wave() = default;


    /*!
     * Updates the wave by making it evolve over time
     * @param dt time since last call to update
     */
    void update(sf::Time dt) override;

    /*!
     * The energy of the wave at it's current propagation state.
     * The propagation of the wave is based of the timeOfPropagation
     * @return energy of the wave
     */
    double getEnergy() const;

    /*!
     * Current intensity of the wave
     * The intensity of the wave is based of the timeOfPropagation
     * @return Intensity of the wave
     */
    double getIntensity() const;

    /*!
     * If the intensity of the wave is to weak this method will return true.
     * This method informs caller that this wave should be deleted from the simulation
     * @return true is wave intensity to weak for simulation
     */
    bool isWaveToBeDeleted();

    void draw(sf::RenderTarget &target) const override;
};


#endif //PARTIE1_WAVE_HPP
