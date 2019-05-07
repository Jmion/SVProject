//
// Created by jeremy on 4/1/19.
//

#include "Scorpion.hpp"
#include <Application.hpp>
#include <Random/Uniform.hpp>
#include <string>
#include <Utility/Macros.hpp>

double Scorpion::getStandardMaxSpeed() const
{
    return getAppConfig().scorpion_max_speed;
}

double Scorpion::getMass() const
{
    return getAppConfig().scorpion_mass;
}

double Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

double Scorpion::getViewDistance() const
{
    return getAppConfig().scorpion_view_distance;
}

double Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
}

double Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
}

double Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

Scorpion::~Scorpion() = default;

double Scorpion::getSize() const
{
    return getAppConfig().scorpion_size;
}

double Scorpion::getInitialEnergy() const
{
    return getAppConfig().scorpion_energy_initial;
}

Scorpion::Scorpion(const Vec2d &position, double energyLevel, bool isFemale) : Animal(position, getSize(), energyLevel,
            isFemale)
{
}

Scorpion::Scorpion(const Vec2d &position) : Scorpion(position, getInitialEnergy(), uniform(0, 1) == 0)
{

}

const std::string Scorpion::getTexturePath() const
{
    return getAppConfig().scorpion_texture;
}

bool Scorpion::eatable(OrganicEntity const *entity) const
{
    return entity->eatableBy(this);
}

bool Scorpion::eatableBy(A_Unused Scorpion const *scorpion) const
{
    return false;
}

bool Scorpion::eatableBy(A_Unused Gerbil const *gerbil) const
{
    return false;
}

bool Scorpion::eatableBy(A_Unused Food const *food) const
{
    return false;
}

sf::Time Scorpion::getLongevity() const
{
    return getAppConfig().scorpion_longevity;
}

double Scorpion::getEnergyLossFactor() const
{
    return getAppConfig().scorpion_energy_loss_factor;
}

double Scorpion::getStarvingEnergyLevel() const
{
    return getAppConfig().scorpion_energy_starving;
}

bool Scorpion::matable(OrganicEntity const *other) const {
    return other->canMate(this);
}

bool Scorpion::canMate(Scorpion const *scorpion) const {
    return Animal::canMate(scorpion);
}

bool Scorpion::canMate(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Scorpion::canMate(A_Unused Food const *food) const {
    return false;
}

double Scorpion::getMinimumMatingEnergyMale() const {
    return getAppConfig().scorpion_energy_min_mating_male;
}

double Scorpion::getMinimumMatingEnergyFemale() const {
    return getAppConfig().scorpion_energy_min_mating_male;
}

double Scorpion::getMinimumMatingAge() const {
    return getAppConfig().scorpion_min_age_mating;
}

bool Scorpion::meet(OrganicEntity *mate) {
    return mate->meetManagement(this);
}

bool Scorpion::meetManagement(Scorpion *mate) {
    procreate();
    mate->procreate();

    return true;
}

bool Scorpion::meetManagement(A_Unused Gerbil *mate) {
    return false;
}

bool Scorpion::meetManagement(A_Unused Food *mate) {
    return false;
}

double Scorpion::getEnergyLossFemalePerChild() const {
    return getAppConfig().scorpion_energy_loss_female_per_child;
}

int Scorpion::getMinimumNumberOfChildren() const {
    return getAppConfig().scorpion_min_children;
}

int Scorpion::getMaximumNumberOfChildren() const {
    return getAppConfig().scorpion_max_children;
}

double Scorpion::getGestationTimeConfig() const {
    if (getIsFemale())
        return getAppConfig().scorpion_gestation_time;
    return 0;
}

double Scorpion::getEnergyLossMaleMatting() const {
    return getAppConfig().scorpion_energy_loss_mating_male;
}

bool Scorpion::giveBirth() {
    if(Animal::giveBirth()){
        for(int i(0); i < getNumberOfChildren(); i++) {
            getAppEnv().addEntity(new Scorpion(getPosition()));
        }
        return true;
    }
    return false;
}

