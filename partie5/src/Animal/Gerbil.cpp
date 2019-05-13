//
// Created by jeremy on 4/1/19.
//

#include "Gerbil.hpp"
#include <Application.hpp>
#include <random>
#include <Random/Uniform.hpp>
#include <Utility/Macros.hpp>

double Gerbil::getRandomWalkJitter() const
{
    return getAppConfig().gerbil_random_walk_jitter;
}

double Gerbil::getStandardMaxSpeed() const
{
    return getAppConfig().gerbil_max_speed;
}

double Gerbil::getMass() const
{
    return getAppConfig().gerbil_mass;
}

double Gerbil::getViewRange() const
{
    return getAppConfig().gerbil_view_range;
}

double Gerbil::getViewDistance() const
{
    return getAppConfig().gerbil_view_distance;
}

double Gerbil::getRandomWalkRadius() const
{
    return getAppConfig().gerbil_random_walk_radius;
}

double Gerbil::getRandomWalkDistance() const
{
    return getAppConfig().gerbil_random_walk_distance;
}

double Gerbil::getSize() const
{
    return getAppConfig().gerbil_size;
}

double Gerbil::getInitialEnergy() const
{
    return getAppConfig().gerbil_energy_initial;
}

Gerbil::Gerbil(const Vec2d &position, double energyLevel, bool isFemale) : Animal(position, getSize(), energyLevel,
            isFemale)
{
    registerAnimalWithEnvironment();
}

Gerbil::Gerbil(const Vec2d &position) : Gerbil(position, getInitialEnergy(), uniform(0, 1) == 0) {}

Gerbil::~Gerbil() {
    removeAnimalWithEnvironment();
}

bool Gerbil::eatable(OrganicEntity const *entity) const
{
    return entity->eatableBy(this);
}

bool Gerbil::eatableBy(A_Unused Scorpion const * scorpion) const
{
    return true;
}

bool Gerbil::eatableBy(A_Unused Gerbil const *gerbil) const
{
    return false;
}

bool Gerbil::eatableBy(A_Unused Food const *food) const
{
    return false;
}


bool Gerbil::matable(OrganicEntity const *other) const {
    return other->canMate(this);
}

bool Gerbil::canMate(A_Unused Scorpion const *scorpion) const {
    return false;
}

bool Gerbil::canMate(Gerbil const *gerbil) const {
    return Animal::canMate(gerbil);
}

bool Gerbil::canMate(A_Unused Food const *food) const {
    return false;
}


const std::string Gerbil::getTexturePath() const
{
    if (getIsFemale())
        return getAppConfig().gerbil_texture_female;
    return getAppConfig().gerbil_texture_male;
}

sf::Time Gerbil::getLongevity() const
{
    return getAppConfig().gerbil_longevity;
}


double Gerbil::getEnergyLossFactor() const
{
    return getAppConfig().gerbil_energy_loss_factor;
}

double Gerbil::getStarvingEnergyLevel() const
{
    return getAppConfig().gerbil_energy_starving;
}

double Gerbil::getMinimumMatingEnergyMale() const {
    return getAppConfig().gerbil_energy_min_mating_male;
}

double Gerbil::getMinimumMatingEnergyFemale() const {
    return getAppConfig().gerbil_energy_min_mating_female;
}

double Gerbil::getMinimumMatingAge() const {
    return getAppConfig().gerbil_min_age_mating;
}



bool Gerbil::meetManagement(Gerbil *mate) {
    procreate();
    mate->procreate();
    return true;
}

bool Gerbil::meetManagement(A_Unused Scorpion *mate) {
    return false;
}

bool Gerbil::meetManagement(A_Unused Food *mate) {
    return false;
}

double Gerbil::getEnergyLossFemalePerChild() const {
    return getAppConfig().gerbil_energy_loss_female_per_child;
}

int Gerbil::getMinimumNumberOfChildren() const {
    return getAppConfig().gerbil_min_children;
}

int Gerbil::getMaximumNumberOfChildren() const {
    return getAppConfig().gerbil_max_children;
}

double Gerbil::getGestationTimeConfig() const {
    if(getIsFemale())
        return getAppConfig().gerbil_gestation_time;
    return 0;
}

double Gerbil::getEnergyLossMaleMatting() const {
    return getAppConfig().gerbil_energy_loss_mating_male;
}

bool Gerbil::meet(OrganicEntity *mate) {
    return mate->meetManagement(this);
}

bool Gerbil::giveBirth() {
    if(Animal::giveBirth()){
        for(int i(0); i < getNumberOfChildren(); i++){
            getAppEnv().addEntity(new Gerbil(getPosition()));
        }
        return true;
    }
    return false;
}

void Gerbil::registerAnimalWithEnvironment() const {
    getAppEnv().addGerbil();
}

void Gerbil::removeAnimalWithEnvironment() const {
    getAppEnv().removeGerbil();
}

