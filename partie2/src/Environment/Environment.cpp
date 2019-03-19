//
// Created by jeremy on 3/17/19.
//

#include "Environment.hpp"
#include <Animal/Animal.hpp>

/*!
 * Add animal to environment fauna.
 * @param animal
 */
void Environment::addAnimal(Animal* animal){
    animals.push_back(animal);
}

/*!
 * Add ressources to environment. These are targets for the fauna. (Food)
 * @param target of the resource to add to the environment
 */
void Environment::addTarget(const Vec2d& target){
    targets.push_back(target); //we can pass a ref since the method copies the reference when adding to list
}

/*!
 * Make the animals in the environment evolve.
 * @param dt time between updates
 */
void Environment::update(sf::Time dt){
    for(auto a : animals){
        a->update(dt);
    }
}

/*!
 * draws the animals and targets onto the window
 * @param targetWindow to display on
 */
void Environment::draw(sf::RenderTarget& targetWindow) const{
    for(Animal* a: animals){
        a->draw(targetWindow);
    }

    sf::Color red(255,0,0);
    for(const auto& t : targets){
        targetWindow.draw(buildCircle(t,5,red));
    }
}


/*!
 * Removes all animals and targets from the environment.
 */
void Environment::clean() {
    for(Animal* a: animals){
        delete (a);
    }
    animals.clear();
    targets.clear();
};
/*!
 * Will free all the animals attached to it.
 */
Environment::~Environment(){
    for (Animal *a: animals) {
        delete (a);
    }
    //TODO complete this methode
}

std::list<Vec2d> Environment::getTargetsInSightForAnimal(Animal* animal){
    std::list<Vec2d> targetsInSight;
    for(const Vec2d& t: targets){
        if (animal->isTargetInSight(t)) {
            targetsInSight.push_back(t);
        }
    }
    return targetsInSight;
}
