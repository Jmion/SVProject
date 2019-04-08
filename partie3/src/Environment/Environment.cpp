//
// Created by jeremy on 3/17/19.
//

#include "Environment.hpp"
#include <Animal/Animal.hpp>
#include <Environment/OrganicEntity.hpp>

/*!
 * Add animal to environment fauna.
 * @param animal
 */
void Environment::addEntity(OrganicEntity* entity){
    //TODO could imagine copying the animal passed in to gurantee that there will be not issues with organicEntities in a list that no not exist.
    if(entity != nullptr){
        organicEntities.push_back(entity);
    }else{
        std::cerr<< "Attempt to add entity that is a nullprt"<<std::endl;
    }
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
    for(OrganicEntity* o : organicEntities){
        o->update(dt);
    }

    for(FoodGenerator& generator: generators){
        generator.update(dt);
    }
}

/*!
 * draws the animals and targets onto the window
 * @param targetWindow to display on
 */
void Environment::draw(sf::RenderTarget& targetWindow) const{
    for(OrganicEntity* o: organicEntities){
        o->draw(targetWindow);
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
    for(OrganicEntity* o: organicEntities){
        delete (o);
        o = nullptr;
    }
    organicEntities.clear();
    targets.clear();
};
/*!
 * Will free all the animals attached to it.
 */
Environment::~Environment(){
    for (OrganicEntity *o: organicEntities) {
        if(o!= nullptr){
            delete (o);
            o = nullptr;
        }
    }
}

//TODO check complexity of this call
std::list<OrganicEntity*> Environment::getEntitiesInSightForAnimal(Animal* animal){
    std::list<OrganicEntity*> targetsInSight;
    for(OrganicEntity* entity: organicEntities){
        if (animal->isTargetInSight(entity->getPosition())) {
            targetsInSight.push_back(entity);
        }
    }
    return targetsInSight;
}

void Environment::addGenerator(const FoodGenerator &foodGenerator) {
    generators.push_back(foodGenerator);
}
