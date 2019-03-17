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

    ChasingAutomaton(const Vec2d& _postion);

protected:


    Vec2d attractionForce() const ;

    Vec2d updateMovementVariables(const Vec2d& acceleration, const sf::Time dt );


private:
    double speed;
    double maxSpeed=0; //what is this for???
    double mass =0; //what are we using this for????
    Vec2d direction, targetPosition;
    Deceleration deceleration;

    double getDecelerationRate() const;

};


#endif //INFOSV_CHASINGAUTOMATON_HPP
