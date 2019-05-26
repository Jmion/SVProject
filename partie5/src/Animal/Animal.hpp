//
// Created by jeremy on 3/17/19.
//

#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Utility.hpp>
#include <Environment/OrganicEntity.hpp>
#include <string>
#include <list>
#include <Utility/Macros.hpp>
#include <array>

class Animal : public OrganicEntity
{
public:
    /*!
     * Allow modification of target position
     * @param target position of chasing automaton
     * @return Reference to this to allow chaining calls
     */
    Animal &setTargetPosition(const Vec2d &target);

    virtual ~Animal() = default;

    /*!
     * Amount of deceleration that the automaton has when approaching the target.
     */
    /*
     * If adding new states to this enum do not forget to configure the values that are wanted
     * in the getDecelerationRate method present in this class.
     */
    enum Deceleration {
        WEAK, MEDIUM, STRONG
    };


    /*!
     * The action decide how the animal is currently behaving. These are the different states that the animal
     * can be in.
     */
    DEFINE_ENUM_WITH_STRING_CONVERSIONS(State, (FOOD_IN_SIGHT)(FEEDING)(RUNNING_AWAY)
                                        (MATE_IN_SIGHT)(MATING)(GIVING_BIRTH)(WANDERING)(DIESTING))


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
     * Calculates the speed vector of the automaton
     * @return
     */
    Vec2d getSpeedVector() const;


    /*!
     * Calculates the position and speed of the automaton.
     * @param dt time since previous update
     */
    void update(sf::Time dt) override;


    /*!
     * draws the automaton and it's target in the targetWindow
     * @param targetWindow where to draw the automaton
     */
    void draw(sf::RenderTarget &targetWindow) const override;

    /*!
     * Creates a new ChasingAutomaton. The deceleration parameter allows for the control of how fast the automaton slows down
     * when approaching it's target.
     * @param _position starting position of the automaton
     * @param size of the animal in the simulation
     * @param energy level of the organic entity
     * @param isFemale that indicates the sex of the animal. If true the sex is female.
     * @param _deceleration constant that defines how quickly the automatons will slow down when approaching there target.
     */
    Animal(const Vec2d &_position, double size, double energyLevel, bool isFemale, Deceleration _deceleration = WEAK);

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
    bool isTargetInSight(const Vec2d &target) const;


    /*!
     * Allows modification of the deceleration rate
    * @param decel the new deceleration rate
    */
    void setDeleleration(Deceleration decel);


    /*!
     * @return Getter for target position
     */
    virtual const Vec2d &getTargetPosition() const;

protected:


    /*!
    * registers animal with environment
    */
    virtual void registerAnimalWithEnvironment(std::string) const;

    /*!
     * Removes animal from environment
     */
    virtual void removeAnimalWithEnvironment(std::string) const;

    /*!
     * @return string representation of the state
     */
    virtual std::string getStateString() const;

    /*!
    * Converts from animal coordinates to global coordinates.
    * @param v in animal coordinates
    * @return v in the global coordinates
    */
    Vec2d convertToGlobalCoord(const Vec2d &v) const;

    /*!
     * Gets number of children that this animal has.
     * Pregnant animals have children. If the animal is a male then
     * this methode will return 0.
     * @return Number of children that the animal has (pregnancy, number that are going to be born)
     */
    int getNumberOfChildren() const;

    /*!
     * Calculates the attraction force that the automaton is experiencing
     * @return force that are being applied to the robot.
     */
    Vec2d attractionForce() const;


    /*!
    * Changes the direction of the direction vector. The director vector will be worth [cos(angle),sin(angle)]
    * @param angle in radians of the new direction vector
    * @return reference to this
    */
    Animal &setRotation(double angle);

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
     * The minimum amount of energy needed to mate. Male animals
     *
     * @throws runtime_error unsuportedOperation is animal is female
     * @return minimum mating energy for male
     */
    virtual double getMinimumMatingEnergyMale() const = 0;

    /*!
     * The minimum amount of energy needed to mate
     *
     * @throws runtime_error unsuportedOperation is animal is male
     * @return minimum mating energy for male
     */
    virtual double getMinimumMatingEnergyFemale() const = 0;

    /*!
     * The minimum age that an animal must be before being able to reprocude
     * @return min mating age
     */
    virtual double getMinimumMatingAge() const = 0;

    /*!
     * Returns the path to the image of the animal.
     */
    virtual std::string const getTexturePath() const = 0;

    /*!
     * Allows the user to determine the sex fo the animal
     * @return isFemale of of the animal.
     */
    bool getIsFemale() const;

    /*!
     * Is the animal pregnant.
     * All always return false if isFemale returns true
     * @return true if animal is pregnent
     */
    bool getIsPregnant() const;

    /*!
     * Gets the maximum speed that the animal can move given it's current state.
     * @return max move speed of the animal
     */
    virtual double getMaxSpeed() const;

    /*!
     * This method defines the global criteria that determins if 2 animals can mate.
     * @param partner that we want to check if we can mate with
     * @return true if mate is available for mating.
     */
    virtual bool canMate(Animal const *partner) const;

    /*!
     * Amount of energy lost per children born
     * @return energy required per children
     */
    virtual double getEnergyLossFemalePerChild() const = 0;

    /*!
     * Gets from the config file the minimum number of children that a pregnant
     * animal can have.
     * @return minimum number of children
     */
    virtual int getMinimumNumberOfChildren() const = 0;


    /*!
     * Gets from the config file the maximum number of children that a pregnant
     * animal can have.
     * @return maximum number of children
     */
    virtual int getMaximumNumberOfChildren() const = 0;

    /*!
     * Time in seconds that the animal needs for gestation
     * @return time in seconds for gestation. If animal is male will return gestation time of 0.
     */
    virtual double getGestationTimeConfig() const = 0;

    /*!
     * Energy lost by male when matting.
     * @return amount of energy lost by male when matting
     */
    virtual double getEnergyLossMaleMatting() const = 0;

    /*!
     * Makes animal fornicate.
     * Will only modify one animal. Needs to be called on both animals fornicating to have the proper effect
     */
    void procreate();

    virtual /*!
    * Updates the time that the entity has spend waiting after matting.
    * It will also return true if it has already waited long enough to allow for state change
    * @param dt time spent since last call
    * @return true if entity has spend at least entity_wait_time waiting after having procreated.
    */
    bool updateAndHasWaitedLongEnoughMatting(sf::Time dt);


    /*!
    * Updates the time that the entity has spend waiting after matting.
    * It will also return true if it has already waited long enough to allow for state change
    * @param dt time spent since last call
    * @return true if entity has spend at least entity_wait_time waiting after having procreated.
    */
    bool updateAndHasWaitedLongEnoughGestationTime(sf::Time dt);


    /*!
     * Update the time that the entity has spend waiting in givingBirth state.
     * It will return true if the animal has spend enough time in givingBirth state.
     * @param dt time spent since last call
     * @return true if animal has spend at least animal_delivery_time is giving birth state. Note methode will return true if called by a male.
     */
    bool updateAndHasWaitedLongEnoughGivingBirthTime(sf::Time dt);

    /*!
    * Creates children on animal if animal is pregnant. And spaws then into the world. Needs to be the same type as the animal that caller is.
    * @return true is sucessfull spawning.
    */
    virtual bool giveBirth();

    /*!
    * Makes the automaton moved based of of the force that it is experiencing.
    * @param force that the robot is experiencing
    * @param dt time that has passed since previous update
    * @param hasTarget true if animal has a real target. If false virtual target will show on debug
    */
    void updateMovementVariables(const Vec2d &force, const sf::Time &dt, bool hasTarget);

    /*!
     * Calculates the force that will slow and stop the animal
     * @return the force to stop the animal
     */
    Vec2d stoppingAttractionForce();

    /*!
     * Generates a virtual target for the animal. It will calculate the attraction force between the target and the animal.
     *
     * The calculation of the force is done as follows: virtualTargetPosition-position
     * @return force vector due to the virtual target
     */
    Vec2d randomWalk();

    /*!
     * Array containing other entities that this animal might react with.
     * For the specifics of what each element of the array is for this animal
     * please refer to the table bellow.
     *
     *
     * +----------+----------------+
     *  | location | description    |
     *  +----------+----------------+
     *  | 0        |                |
     *  |          | Food           |
     *  +----------+----------------+
     *  | 1        | Potential mate |
     *  +----------+----------------+
     *  | 2        | closest Enemy  |
     *  +----------+----------------+
     *
     * Elements of the array will be nullptr if there is no organicEntity that fits the description.
     * @return first element is the organicEntity that is a source of food, second potential mate, third closest enemy.
     */
    std::array<OrganicEntity *, 3> analyseEnvironment();


    /*!
    * Draws the semi circular arc centered on the animal. This is the animals viewing angle
    * @param target that is used to draw on
    */
    void drawVision(sf::RenderTarget &target) const;

    /*!
     * Returns the level of energy at which the animal is considered to be starving
     * @return energy level for starvation
     */
    virtual double getStarvingEnergyLevel() const = 0;


    /*!
     * Returns current state of the animal
     * @return
     */
    State getState() const;

    /*!
     * Reurns current direction of the animal
     */
    Vec2d getDirection() const;

private:



    /*!
     * Current state that the animal is in.
     */
    State state;

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
     * only applies to animals if isFemale is true.
     * Indicates that the animal is pregnant.
     */
    bool isPregnant;


    /*!
     * The number of children that a pregnent animal is carrying.
     */
    int numberOfChildren;


    /*!
     * Deceleration rate when animal approaches target.
     */
    Deceleration deceleration;


    /*!
    * Used to express the wait that the animal has waited after matting
    */
    sf::Time mattingWaitTime;

    /*!
     * Wait that the time that the femal has been pregnent before giving birth
     */
    sf::Time gestationTime;

    /*!
     * Time that the animal has been in GivingBirth state
     */
    sf::Time givingBirthTime;


    /*!
     * List of predators position in sight
     */
    std::list<Vec2d> predatorPosition;


    /*!
     * Updates the state of the animal
     */
    void updateState(sf::Time dt);

    /*!
    * Makes the automaton moved based of of the force that it is experiencing.
    * @param force that the robot is experiencing
    * @param dt time that has passed since previous update
    */
    void updateMovementVariables(const Vec2d &force, const sf::Time &dt);

    /*!
     * This methode will resolve the Deceleration enum to a double value which is the rate of deceleration. It will return the rate of deceleration bassed on the attribute deceleration of the class
     * @return the rate of deceleration
     */
    double getDecelerationRate() const;




    /*!
     * Updates the energy level of the animal given that it has lived for a instant dt.
     * @param dt amount of time since last call to this methode
     */
    void spendEnergy(sf::Time dt);


    /*!
     * Factor that influences how much energy the animal uses when moving.
     * Greater values indicate more energy is being used
     * @return energy loss factor
     */
    virtual double getEnergyLossFactor() const = 0;


    /*!
     * Calculates the repulsive force beween the animal and the predators last know location.
     * @return the force that will act on the animal to make it run away
     */
    Vec2d runningAwayForce();

};


#endif //PARTIE1_ANIMAL_HPP
