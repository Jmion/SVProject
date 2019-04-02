//
// Created by jeremy on 3/17/19.
//

#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>
#include <string>

class Animal: public OrganicEntity {
public:

    /*!
     * Amount of deceleration that the automaton has when approaching the target.
     */
    /*
     * If adding new states to this enum do not forget to configure the values that are wanted
     * in the getDecelerationRate method present in this class.
     */
    enum Deceleration {WEAK,MEDIUM,STRONG};

    /*!
     * Will return values predefined in the config file applying to this.
     * @return  max speed.
     */
    virtual double getStandardMaxSpeed() const = 0;

    /*!
     * Will return values predefined in the config file applying to this
     * @return mass
     */
    virtual double getMass() const = 0;

    /*!
     * Allow modification of target position
     * @param target position of chasing automaton
     * @return Reference to this to allow chaining calls
     */
    Animal& setTargetPosition(const Vec2d& target);


    /*!
     * Calculates the speed vector of the automaton
     * @return
     */
    Vec2d getSpeedVector() const ;


    /*!
     * Calculates the position and speed of the automaton.
     * @param dt time since previous update
     */
    void update(sf::Time dt) override;


    /*!
     * draws the automaton and it's target in the targetWindow
     * @param targetWindow where to draw the automaton
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /*!
     * Creates a new ChasingAutomaton. The deceleration parameter allows for the control of how fast the automaton slows down
     * when approaching it's target.
     * @param _position starting position of the automaton
     * @param size of the animal in the simulation
     * @param energy level of the organic entity
     * @param isFemale that indicates the sex of the animal. If true the sex is female.
     * @param _deceleration constant that defines how quickly the automatons will slow down when approaching there target.
     */
    Animal(const Vec2d& _position, double size, double energyLevel, bool isFemale, Deceleration _deceleration=WEAK);

    /*!
     * @return Viewing animal range in radians
     */
    virtual double getViewRange() const = 0;

    /*!
     * @return Viewing distance for animals
     */
    virtual double getViewDistance() const = 0;

    /*!
     * Will determine if the target can be seen by the Animal
     * @param target that needs to be tested if it can be seen
     * @return true if target can be seen by the animal, false otherwise
     */
    bool isTargetInSight(const Vec2d& target) const;


    /*!
     * Allows modification of the deceleration rate
    * @param decel the new deceleration rate
    */
    void setDeleleration(Deceleration decel);


    /*!
     * Destructor of animal forcing subclasses to define a proper delete.
     */
    virtual ~Animal() = 0;

protected:


    /*!
     * Calculates the attraction force that the automaton is experiencing
     * @return force that are being applied to the robot.
     */
    Vec2d attractionForce() const ;


    /*!
    * Changes the direction of the direction vector. The director vector will be worth [cos(angle),sin(angle)]
    * @param angle in radians of the new direction vector
    * @return reference to this
    */
    Animal& setRotation(double angle);

    /*!
    * @return the angle in radians of the direction vector
    */
    double getRotation() const;

    /*!
    * Radius of the random walk circle
    * @return the radius of the circle
    */
    virtual double getRandomWalkRadius() const = 0;

    /*!
     * Th distance between the center of the circle and the position of the animal
     * @return The distance to the animal from the circle center
     */
    virtual double getRandomWalkDistance() const = 0;

    /*!
     * The amplificaition factor for the amount of jitter of the virtual target
     * @return the amout of jitter amplification
     */
    virtual double getRandomWalkJitter() const = 0;

    /*!
     * The size as configured for the animal in the Config JSON file
     * @return size of the animal. Diameter
     */
    virtual double getSize() const = 0;

    /*!
     * The initial energy of the animal as defined in the config JSON file.
     * @return initial energy level
     */
    virtual double getInitialEnergy() const = 0;


    /*!
     * Returns the path to the image of the animal.
     */
    virtual std::string const getTexturePath() const = 0;

    /*!
     * Allows the user to determine the sex fo the animal
     * @return isFemale of of the animal.
     */
    bool getIsFemale() const;

private:

    /*!
     * speed at which the animal moves
     */
    double speed;

    /*!
     * Indicates if the Animal has a real target. If the animal is following a virtual target this variable needs to be set to false.
     */
    bool hasTarget;

    Vec2d direction, current_target, targetPosition;


    /*!
     * Indicates if the animal is female. If false it is male.
     */
    bool isFemale;

    /*!
     * Deceleration rate when animal approaches target.
     */
    Deceleration deceleration;


    /*!
    * Makes the automaton moved based of of the force that it is experiencing.
    * @param force that the robot is experiencing
    * @param dt time that has passed since previous update
    */
    void updateMovementVariables(const Vec2d& force, const sf::Time dt );

    /*!
     * This methode will resolve the Deceleration enum to a double value which is the rate of deceleration. It will return the rate of deceleration bassed on the attribute deceleration of the class
     * @return the rate of deceleration
     */
    double getDecelerationRate() const;


    /*!
    * Draws the semi circular arc centered on the animal. This is the animals viewing angle
    * @param target that is used to draw on
    */
    void drawVision(sf::RenderTarget& target) const;

    /*!
     * Generates a virtual target for the animal. It will calculate the attraction force between the target and the animal.
     *
     * The calculation of the force is done as follows: virtualTargetPosition-position
     * @return force vector due to the virtual target
     */
    Vec2d randomWalk();

    //Try to const v and ref it
    /*!
     * Converts from animal coordinates to global coordinates.
     * @param v in animal coordinates
     * @return v in the global coordinates
     */
    Vec2d convertToGlobalCoord(const Vec2d& v) const;



};




#endif //PARTIE1_ANIMAL_HPP
