//
// Created by jeremy on 3/17/19.
//

#ifndef INFOSV_ENVIRONMENT_HPP
#define INFOSV_ENVIRONMENT_HPP


#include <Animal/Animal.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <list>

class Environment {
public:
    /*!
     * Add animal to environment fauna.
     * @param animal
     */
    void addAnimal(Animal* animal);

    /*!
     * Add ressources to environment. These are targets for the fauna. (Food)
     * @param target of the resource to add to the environment
     */
    void addTarget(const Vec2d& target);

    /*!
     * Make the animals in the environment evolve.
     * @param dt time between updates
     */
    void update(sf::Time dt);

    /*!
     * draws the animals and targets onto the window
     * @param targetWindow to display on
     */
    void draw(sf::RenderTarget& targetWindow) const;


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
    ~Environment();

private:
std::list<Animal*> animals;
std::list<Vec2d> targets;

};


#endif //PARTIE1_ENVIRONMENT_HPP
