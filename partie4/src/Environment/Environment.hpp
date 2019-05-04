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

class Animal;
class Wave;
class SolideObstacle;

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
    Environment() = default;

    /*!
     * Disabeling copy constructor since this is a large object that should not be copied.
     */
    Environment(const Environment&) = delete;
    Environment& operator=(const Environment& env) = delete;

    /*!
     * Will free all the animals attached to it.
     */
    virtual ~Environment();

    /*!
     * Determins which targets are in sight of the animal.
     * @param animal that is looking for targets
     * @return list of all targets that can be seen by the animal
     */
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(const Animal *animal) const;

    std::list<SolideObstacle*> getSolideObstaclesCollidingForWave(const Wave* wave) const;

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

private:
    std::list<OrganicEntity*> organicEntities;
    std::list<Vec2d> targets;
    std::list<FoodGenerator*> generators;
    std::list<Wave*> waves;
    std::list<SolideObstacle*> solidObstacles;

    /*!
     * Removes organicEntities from the environment list when they are dead
     */
    void cleanUpDeadOrganic();

    /*!
     * Remvoes waves from the environment when there intensity is to low
     */
    void cleanUpWave();
};


#endif //PARTIE1_ENVIRONMENT_HPP
