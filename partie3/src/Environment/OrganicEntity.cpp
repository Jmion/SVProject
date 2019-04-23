//
// Created by jeremy on 4/1/19.
//

#include "OrganicEntity.hpp"
#include <Obstacle/CircularCollider.hpp>
#include <Application.hpp>

OrganicEntity::OrganicEntity(const Vec2d& position, double size, double energyLevel):
    CircularCollider(position,size/2.0),energyLevel(energyLevel), age(sf::Time::Zero),feedingWait(getAppConfig().entity_wait_after_feeding)  {}

double OrganicEntity::getEnergyLevel() const
{
    return energyLevel;
}


double OrganicEntity::getMinEnergy() const
{
    return getAppConfig().animal_min_energy;
}

sf::Time OrganicEntity::getLongevity() const
{
    return sf::seconds(1e9);
}

bool OrganicEntity::isDead() const
{
    return age > getLongevity() || energyLevel < getMinEnergy();
}

const sf::Time &OrganicEntity::getAge() const
{
    return age;
}

void OrganicEntity::aging(sf::Time dt)
{
    age += dt;
}

void OrganicEntity::spendEnergy(double energySpend)
{
    energyLevel -= energySpend;
}

void OrganicEntity::eat(OrganicEntity* &eaten)
{
    if(eaten!= nullptr && eatable(eaten)) {

        energyLevel += eaten->energyLevel * getAppConfig().entity_energy_transfer_factor;
        eaten->energyLevel = 0;
        feedingWait = sf::Time::Zero;
        std::cerr << "end of fofod" << std::endl;
    }
}

bool OrganicEntity::updateAndHasWaitedLongEnough(sf::Time dt)
{
    feedingWait += dt;
    return feedingWait>=getAppConfig().entity_wait_after_feeding;
}

void OrganicEntity::update(sf::Time dt) {
    aging(dt);
}




