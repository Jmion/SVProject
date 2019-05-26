//
// Created by jeremy on 3/17/19.
//

#include "Environment.hpp"
#include <Animal/Animal.hpp>
#include <Animal/Dragon.hpp>
#include <Obstacle/SolideObstacle.hpp>
#include <Environment/OrganicEntity.hpp>
#include <algorithm>
#include <Environment/Wave.hpp>
#include <Application.hpp>
#include <Utility/Constants.hpp>


/*!
 * Add animal to environment fauna.
 * @param animal
 */
void Environment::addEntity(OrganicEntity *entity)
{
    //TODO could imagine copying the animal passed in to gurantee that there will be not issues with organicEntities in a list that no not exist.
    if (entity != nullptr) {
        organicEntities.push_back(entity);
    } else {
        std::cerr << "Attempt to add entity that is a nullprt" << std::endl;
    }
}

/*!
 * Add ressources to environment. These are targets for the fauna. (Food)
 * @param target of the resource to add to the environment
 */
void Environment::addTarget(const Vec2d &target)
{
    targets.push_back(target); //we can pass a ref since the method copies the reference when adding to list
}

/*!
 * Make the animals in the environment evolve.
 * @param dt time between updates
 */
void Environment::update(sf::Time dt)
{

    for (FoodGenerator *generator: generators) {
        generator->update(dt);
    }

    for (auto &o : organicEntities) {
        if (o != nullptr) {
            o->update(dt);
        }
    }

    for (auto &w: waves) {
        if (w != nullptr) {
            w->update(dt);
        }
    }

    cleanUpDeadOrganic();
    cleanUpWave();

    dragonFireTrigger = false;
}

void Environment::cleanUpDeadOrganic()
{
    std::__cxx11::list<OrganicEntity *> toDelete;
    for (OrganicEntity *o : organicEntities) {
        if (o != nullptr && o->isDead()) {
            toDelete.push_back(o);
        }
    }

    for (OrganicEntity *o: toDelete) {
        organicEntities.remove(o);
        delete (o);
    }

    toDelete.clear();
}

void Environment::cleanUpWave()
{
    std::list<Wave *> toDelete;
    for (auto &w: waves) {
        if (w != nullptr && w->isWaveToBeDeleted()) {
            toDelete.push_back(w);
        }
    }

    for (auto &w : toDelete) {
        waves.remove(w);
        delete (w);
    }
    toDelete.clear();
}


/*!
 * draws the animals and targets onto the window
 * @param targetWindow to display on
 */
void Environment::draw(sf::RenderTarget &targetWindow) const
{
    for (OrganicEntity *o: organicEntities) {
        if (o != nullptr)
            o->draw(targetWindow);
    }

    for (auto &w: waves) {
        if (w != nullptr)
            w->draw(targetWindow);
    }

    for (auto &o: solidObstacles) {
        if (o != nullptr)
            o->draw(targetWindow);
    }

    sf::Color red(255, 0, 0);
    for (const auto &t : targets) {
        targetWindow.draw(buildCircle(t, 5, red));
    }

}


/*!
 * Removes all animals and targets from the environment.
 */
void Environment::clean()
{
    for (OrganicEntity *o: organicEntities) {
        delete (o);
        o = nullptr;
    }
    organicEntities.clear();
    targets.clear();
    clearCounter();
}

/*!
 * Will free all the animals attached to it.
 */
Environment::~Environment()
{
    for (OrganicEntity *o: organicEntities) {
        if (o != nullptr) {
            delete (o);
        }
    }

    for (Wave *w: waves) {
        if (w != nullptr) {
            delete (w);
        }
    }

    for (SolideObstacle *s : solidObstacles) {
        if (s != nullptr) {
            delete (s);
        }
    }

    for (auto gen : generators) {
        if (gen != nullptr) {
            delete (gen);
        }
    }

    organicEntities.clear();
    waves.clear();
    solidObstacles.clear();
    generators.clear();
    dragonCommand.stop();
}

std::list<OrganicEntity *> Environment::getEntitiesInSightForAnimal(const Animal *animal) const
{
    std::list<OrganicEntity *> targetsInSight;
    for (OrganicEntity *entity: organicEntities) {
        if (animal->isTargetInSight(entity->getPosition())) {
            targetsInSight.push_back(entity);
        }
    }
    return targetsInSight;
}

std::list<OrganicEntity *> Environment::getEntitiesInBurnRangeOfDragon(const Dragon *dragon) const
{
    std::list<OrganicEntity *> targetsInSight;
    for (OrganicEntity *entity: organicEntities) {
        if (dragon->isTargetInBurnRange(entity->getPosition())) {
            targetsInSight.push_back(entity);
        }
    }
    return targetsInSight;
}

void Environment::addGenerator(FoodGenerator *foodGenerator)
{
    generators.push_back(foodGenerator);
}

void Environment::addWave(Wave *wave)
{
    waves.push_back(wave);
}

void Environment::addObstacle(SolideObstacle *obstacle)
{
    solidObstacles.push_back(obstacle);
}

std::list<SolideObstacle *> Environment::getSolideObstaclesCollidingForWave(const Wave *wave) const
{
    std::list<SolideObstacle *> solideObstaclesCol;
    for (auto &s : solidObstacles) {
        if (s != nullptr && wave->isColliding(*s) && !wave->isCircularColliderInside(*s))
            solideObstaclesCol.push_back(s);
    }
    return solideObstaclesCol;

}

std::list<Wave *> Environment::getWaveCollidingWithSensor(const Vec2d &v) const
{
    std::list<Wave *> wavesColliding;
    for (auto &w: waves) {
        double ditanceFromWaveCenter = (v - w->getPosition()).length();
        double delta = getAppConfig().wave_on_wave_marging;
        if (w->getRadius() - delta <= ditanceFromWaveCenter &&
            w->getRadius() + delta >= ditanceFromWaveCenter) {
            wavesColliding.push_back(w);
        }
    }
    return wavesColliding;
}


std::unordered_map<std::string, double> Environment::fetchData(const std::string &graphTitle)
{
    if (graphTitle == s::GENERAL) {
        entityCounter.at(s::WAVES) = waves.size();
        return entityCounter;
    }
    return std::unordered_map<std::string, double>();
}

Environment::Environment() : dragonFireTrigger(false)
{
    sf::SoundBuffer buffer;
    dragonCommandBuffer.loadFromFile(getAppConfig().dragon_burn_command_sound);
    dragonCommand.setBuffer(dragonCommandBuffer);
    clearCounter();
}

void Environment::clearCounter()
{
    entityCounter.insert(std::pair<std::string, double>(s::GERBILS, 0));
    entityCounter.insert(std::pair<std::string, double>(s::SCORPIONS, 0));
    entityCounter.insert(std::pair<std::string, double>(s::FOOD, 0));
    entityCounter.insert(std::pair<std::string, double>(s::NEURONAL, 0));
    entityCounter.insert(std::pair<std::string, double>(s::WAVES, 0));
    entityCounter.insert(std::pair<std::string, double>(s::DRAGON, 0));

}

void Environment::incrementCounter(const std::string &animalType)
{
    if (entityCounter.find(animalType) != entityCounter.end()) {
        entityCounter[animalType] += 1;
    }
}

void Environment::decrementCounter(const std::string &animalType)
{
    auto it = entityCounter.find(animalType);
    if (it != entityCounter.end() && it->second > 0) {
        entityCounter[animalType] -= 1;
    }
}

bool Environment::isDragonFireTrigger() const
{
    return dragonFireTrigger;
}

void Environment::setDragonFireTrigger(bool dragonFireTrigger)
{
    Environment::dragonFireTrigger = dragonFireTrigger;
    if (dragonFireTrigger) {
        if (entityCounter[s::DRAGON] > 0) {
            dragonCommand.play();
        }
    }
}







