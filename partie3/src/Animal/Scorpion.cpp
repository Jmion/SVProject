//
// Created by jeremy on 4/1/19.
//

#include "Scorpion.hpp"
#include <Application.hpp>
#include <Random/Uniform.hpp>
#include <string>
#include <Utility/Macros.hpp>

double Scorpion::getStandardMaxSpeed() const {
    return getAppConfig().scorpion_max_speed;
}

double Scorpion::getMass() const {
    return getAppConfig().scorpion_mass;
}

double Scorpion::getViewRange() const {
    return getAppConfig().scorpion_view_range;
}

double Scorpion::getViewDistance() const {
    return getAppConfig().scorpion_view_distance;
}

double Scorpion::getRandomWalkRadius() const {
    return getAppConfig().scorpion_random_walk_radius;
}

double Scorpion::getRandomWalkDistance() const {
    return getAppConfig().scorpion_random_walk_distance;
}

double Scorpion::getRandomWalkJitter() const {
    return getAppConfig().scorpion_random_walk_jitter;
}

Scorpion::~Scorpion() = default;

double Scorpion::getSize() const {
    return getAppConfig().scorpion_size;
}

double Scorpion::getInitialEnergy() const {
    return getAppConfig().scorpion_energy_initial;
}

Scorpion::Scorpion(const Vec2d &position, double energyLevel, bool isFemale) : Animal(position, getSize(), energyLevel,
                                                                                      isFemale) {
}

Scorpion::Scorpion(const Vec2d &position) : Scorpion(position, getInitialEnergy(), uniform(0, 1) == 0) {

}

const std::string Scorpion::getTexturePath() const {
    return getAppConfig().scorpion_texture;
}

bool Scorpion::eatable(OrganicEntity const *entity) const {
    return entity->eatableBy(this);
}

bool Scorpion::eatableBy(A_Unused Scorpion const *scorpion) const {
    return false;
}

bool Scorpion::eatableBy(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Scorpion::eatableBy(A_Unused Food const *food) const {
    return false;
}

