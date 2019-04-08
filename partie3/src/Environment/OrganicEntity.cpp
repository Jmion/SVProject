//
// Created by jeremy on 4/1/19.
//

#include "OrganicEntity.hpp"
#include <Obstacle/CircularCollider.hpp>
#include <Application.hpp>

OrganicEntity::OrganicEntity(const Vec2d& position, double size, double energyLevel):
        CircularCollider(position,size/2.0),energyLevel(energyLevel), age(sf::Time::Zero)  {}

double OrganicEntity::getEnergyLevel() const{
    return energyLevel;
}


double OrganicEntity::getMinEnergy() const {
    return getAppConfig().animal_min_energy;
}

sf::Time OrganicEntity::getLongevity() const {
    return sf::seconds(1e9);
}

bool OrganicEntity::isDead() const {
    return age > getLongevity() || energyLevel < getMinEnergy();
}

const sf::Time &OrganicEntity::getAge() const {
    return age;
}

void OrganicEntity::aging(sf::Time dt) {
    age += dt;
}

void OrganicEntity::spendEnergy(double energySpend) {
    energyLevel -= energySpend;
}


