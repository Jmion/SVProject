//
// Created by jeremy on 3/17/19.
//

#ifndef INFOSV_ENVIRONMENT_HPP
#define INFOSV_ENVIRONMENT_HPP


#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <list>
#include <Environment/OrganicEntity.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <Environment/FoodGenerator.hpp>
#include <Utility/Vec2d.hpp>
#include <unordered_map>
#include <SFML/Audio.hpp>


class Animal;
class Wave;
class SolideObstacle;
class NeuronalScorpion;

class Environment : public Drawable, public Updatable
{
public:
    /*!
     * Add animal to environment fauna.
     * @param animal
     */
    void addEntity(OrganicEntity* entity);

    /*!
     * Add ressources to environment. These are targets for the fauna. (Food)
     * @param target of the resource to add to the environment
     */
    void addTarget(const Vec2d& target);

    /*!
     * Make the animals in the environment evolve.
     * @param dt time between updates
     */
    void update(sf::Time dt) override;

    /*!
     * draws the animals and targets onto the window
     * @param targetWindow to display on
     */
    void draw(sf::RenderTarget& targetWindow) const override;


    /*!
     * Removes all animals and targets from the environment.
     */
    void clean();

    /*!
     * Default constructor
     */
    Environment();

    /*!
     * Disabeling copy constructor since this is a large object that should not be copied.
     */
    Environment(const Environment&) = delete;
    Environment& operator=(const Environment& env) = delete;

    /*!
     * Will free all the animals attached to it.
     */
    ~Environment() override ;

    /*!
     * Determins which targets are in sight of the animal.
     * @param animal that is looking for targets
     * @return list of all targets that can be seen by the animal
     */
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(const Animal *animal) const;

    /*!
     * Determins which targets are within burn range of dragon
     * @param dragon that is going to breath fire
     * @return list of all targets that can be burnt from this dragon
     */
    std::list<OrganicEntity*> getEntitiesInBurnRangeOfDragon(const Dragon * dragon) const;

    /*!
     * Allows access to solideObstacles that are currently colliding with wave
     * @param wave that is being used to know what it is hitting
     * @return list of obstacles that the wave is colliding with.
     */
    std::list<SolideObstacle*> getSolideObstaclesCollidingForWave(const Wave* wave) const;

    /*!
     * Allows access to Waves that are currently colliding with sensor
     * @param location of the sensor
     * @return list of waves that are colliding with the sensor
     */
    std::list<Wave *> getWaveCollidingWithSensor(const Vec2d& location ) const;

    /*!
     * Adds a FoodGenerator to the list of generators.
     * @param foodGenerator being added to the environment
     */
    void addGenerator(FoodGenerator* foodGenerator);

    /*!
     * Adds a Wave to the list of waves.
     * @param wave being added to the environment
     */
    void addWave(Wave* wave);

    /*!
     * Adds a solide obstacle to the list of obstacles
     * @param obstacle being added to the environment
     */
    void addObstacle(SolideObstacle* obstacle);

    /*!
     * Calculates the number of each time of animal that the environment has
     * @param graphTitle
     * @return a map containing the name of the animal, and how many instances of it are in the environment
     */
    std::unordered_map<std::string,double> fetchData(const std::string& graphTitle);

    /*!
     * If counter exsits in entityCounter increments the counter. Otherwise does nothing
     * @param animalType string constant from Utility/Constant.h that are unqiue to the animal
     */
    void incrementCounter(const std::string& animalType);
    /*!
     * If counter exsits in entityCounter decrements the counter. Otherwise does nothing
     * @param animalType string constant from Utility/Constant.h that are unqiue to the animal
     */
    void decrementCounter(const std::string& animalType);

    /*!
     * @return true to indicate that dragons need to spit fire
     */
    bool isDragonFireTrigger() const;

    /*!
     * @param dragonFireTrigger allows for the user to activate dragon fire.
     */
    void setDragonFireTrigger(bool dragonFireTrigger);

private:
    std::list<OrganicEntity*> organicEntities;
    std::list<Vec2d> targets;
    std::list<FoodGenerator*> generators;
    std::list<Wave*> waves;
    std::list<SolideObstacle*> solidObstacles;
    /*!
     * Counts the number of entities that are registered in the environment
     */
    std::unordered_map<std::string,double> entityCounter;

    /*!
     * Removes organicEntities from the environment list when they are dead
     */
    void cleanUpDeadOrganic();

    /*!
     * Remvoes waves from the environment when there intensity is to low
     */
    void cleanUpWave();

    /*!
     * resets all the
     */
    void clearCounter();

    /*!
     * Used as triger to tell all dragons to spit fire.
     */
    bool dragonFireTrigger;

    /*!
     * Sound to play when dragons are instructed to fire.
     */
    sf::Sound dragonCommand;
    /*!
     * Sound buffer to play when dragons are instructed to fire.
     */
    sf::SoundBuffer dragonCommandBuffer;

};


#endif //PARTIE1_ENVIRONMENT_HPP
