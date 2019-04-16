//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_ORGANICENTITY_HPP
#define PARTIE1_ORGANICENTITY_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
class Scorpion;
class Gerbil;
class Food;


class OrganicEntity : public CircularCollider, public Updatable
{
public:
    /*!
     * Creates an organic entity
     * @param position that the organic entity will be placed initially
     * @param size of the organic entity (diameter of the organic entity) The collider ascociated to this shape is 1/2 of size
     * @param energyLevel of the organic entity.
     */
    OrganicEntity(const Vec2d& position, double size, double energyLevel);


    /*!
     * Determins if the organic entity is dead.
     *
     * An organic entity is considered to be dead when it has less energy than
     * the value returned by getMinEnergy, or is it's age is greated than is longevity
     * @return
     */
    bool isDead() const;

    /*!
     * Determins if entity is eatable.
     *
     * To achive this this methode uses double dispatche. It will call the methode eatableBy.
     * This allows the management of how can eat each animal up to itself. this is usefull
     * because it gives the management to the animal itself
     * @param entity that we want to know if this can eat
     * @return true if it is eatable
     */
    virtual bool eatable(OrganicEntity const* entity) const = 0;

    /*!
    * Determins if this can be eaten by a scorpion.
    */
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;
    /*!
     * Determins if this can be eaten by a gerbil.
     */
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    /*!
     * Determins if this can be eaten by a food.
     */
    virtual bool eatableBy(Food const* food) const = 0;

    /*!
     * Getter to current energy level.
     * @return energy level
     */
    double getEnergyLevel() const;

    /*!
     * Increases the animals age by dt
     * @param dt time to add to age
     */
    void aging(sf::Time dt);

    /*!
     * Reduces the energyLevel by energySpend
     * @param energySpend is the amount of energy that has been used
     */
    void spendEnergy(double energySpend);

    /*!
     * Gettier to current age of the organicEntity
     * @return age
     */
    const sf::Time &getAge() const;

protected:

    /*!
     * Allows this to eat another organic entity. Eating an organic entity will cause the energy level of the animal eating
     * to increase.
     * @param eaten organic entity. The organic entity that is for supper.
     */
    void eat(OrganicEntity* & eaten);

    /*!
     * Updates the time that the entity has spend waiting after feeding.
     * It will also return if it has already waited long enough to allow for state change
     * @param dt time spent since last call
     * @return true if entity has spend at least entity_wait_time waiting after having eaten.
     */
    bool updateAndHasWaitedLongEnough(sf::Time dt);

private:


    /*!
     * Returns the minimum amount of energy that an organic entity needs to have
     * to stay alive
     * @return min amount of energy for survival
     */
    virtual double getMinEnergy() const;

    /*!
     * How old can an OrganicEntity live before it dies.
     * @return max age of organic entity
     */
    virtual sf::Time getLongevity() const;


    /*!
     * Energy level of the animal
     */
    double  energyLevel;

    /*!
     * How long the animal has been born. Affected by update
     */
    sf::Time age;

    /*!
     * This varaible is used to express the wait time that the Orgnaic entity has before being able to continue to
     * change state.
     */
    sf::Time feedingWait;

};


#endif //PARTIE1_ORGANICENTITY_HPP
