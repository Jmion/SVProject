//
// Created by jeremy on 4/1/19.
//

#include "OrganicEntity.hpp"
#include <Obstacle/CircularCollider.hpp>
#include <Application.hpp>

OrganicEntity::OrganicEntity(const Vec2d& position, double size, double energyLevel):
        CircularCollider(position,size/2.0),energyLevel(energyLevel)  {}

double OrganicEntity::getEngeryLevel() const{
    return energyLevel;
}


