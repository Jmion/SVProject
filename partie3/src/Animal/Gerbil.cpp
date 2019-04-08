//
// Created by jeremy on 4/1/19.
//

#include "Gerbil.hpp"
#include <Application.hpp>
#include <random>
#include <Random/Uniform.hpp>
#include <Utility/Macros.hpp>

double Gerbil::getRandomWalkJitter() const {
    return getAppConfig().gerbil_random_walk_jitter;
}

double Gerbil::getStandardMaxSpeed() const {
    return getAppConfig().gerbil_max_speed;
}

double Gerbil::getMass() const {
    return getAppConfig().gerbil_mass;
}

double Gerbil::getViewRange() const {
    return getAppConfig().gerbil_view_range;
}

double Gerbil::getViewDistance() const {
    return getAppConfig().gerbil_view_distance;
}

double Gerbil::getRandomWalkRadius() const {
    return getAppConfig().gerbil_random_walk_radius;
}

double Gerbil::getRandomWalkDistance() const {
    return getAppConfig().gerbil_random_walk_distance;
}

double Gerbil::getSize() const { return getAppConfig().gerbil_size; }

double Gerbil::getInitialEnergy() const { return getAppConfig().gerbil_energy_initial; }

Gerbil::Gerbil(const Vec2d &position, double energyLevel, bool isFemale) : Animal(position, getSize(), energyLevel,
                                                                                  isFemale) {
}

Gerbil::Gerbil(const Vec2d &position) : Gerbil(position, getInitialEnergy(), uniform(0, 1) == 0) {}

Gerbil::~Gerbil(){
}

const std::string Gerbil::getTexturePath() const {
    if (getIsFemale())
        return getAppConfig().gerbil_texture_female;
    return getAppConfig().gerbil_texture_male;
}


bool Gerbil::eatable(OrganicEntity const *entity) const {
    return entity->eatableBy(this);
}

bool Gerbil::eatableBy(A_Unused Scorpion const * scorpion) const {
    return true;
}

bool Gerbil::eatableBy(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Gerbil::eatableBy(A_Unused Food const *food) const {
    return false;
}

sf::Time Gerbil::getLongevity() const {
    return getAppConfig().gerbil_longevity;
}
