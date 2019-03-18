//
// Created by jeremy on 3/17/19.
//

#ifndef INFOSV_CHASINGAUTOMATON_HPP
#define INFOSV_CHASINGAUTOMATON_HPP

#include <Utility/Utility.hpp>
#include <Obstacle/CircularCollider.hpp>

class ChasingAutomaton: public CircularCollider {
public:
    enum Deceleration {WEAK,MEDIUM,STRONG};

    /*!
     * Will return values predefined in the config file applying to this.
     * @return  max speed.
     */
    double getStandardMaxSpeed() const;

    /*!
     * Will return values predefined in the config file applying to this
     * @return mass
     */
    double getMass() const;

    /*!
     * Allow modification of target position
     * @param target position of chasing automaton
     * @return Reference to this to allow chaining calls
     */
    ChasingAutomaton& setTargetPosition(const Vec2d& target);


    /*!
     * Calculates the speed vector of the automaton
     * @return
     */
    Vec2d getSpeedVector() const ;


    /*!
     * Calculates the position and speed of the automaton.
     * @param dt time since previous update
     */
    void update(sf::Time dt);


    /*!
     * draws the automaton and it's target in the targetWindow
     * @param targetWindow where to draw the automaton
     */
    void draw(sf::RenderTarget& targetWindow);

    /*!
     * Creates a new ChasingAutomaton. The deceleration parameter allows for the control of how fast the automaton slows down
     * when approaching it's target.
     * @param _position starting position of the automaton
     * @param _deceleration constant that defines how quickly the automatons will slow down when approaching there target.
     */
    ChasingAutomaton(const Vec2d& _position, Deceleration _deceleration=STRONG);


protected:


    Vec2d attractionForce() const ;

    void updateMovementVariables(const Vec2d& acceleration, const sf::Time dt );


private:
    double speed;
    Vec2d direction, targetPosition;
    Deceleration deceleration;

    double getDecelerationRate() const;

};


#endif //INFOSV_CHASINGAUTOMATON_HPP
