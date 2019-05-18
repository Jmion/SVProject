//
// Created by jeremy on 5/13/19.
//

#include <Application.hpp>
#include "Dragon.hpp"
#include <Random/Uniform.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Audio.hpp>

double Dragon::getStandardMaxSpeed() const {
    return getAppConfig().dragon_max_speed;
}

double Dragon::getMass() const {
    return getAppConfig().dragon_mass;
}

double Dragon::getViewRange() const {
    return getAppConfig().dragon_view_range;
}

double Dragon::getViewDistance() const {
    return getAppConfig().dragon_view_distance;
}

bool Dragon::eatable(OrganicEntity const *entity) const {
    return entity->eatableBy(this);
}

bool Dragon::eatableBy(A_Unused Scorpion const *scorpion) const {
    return false;
}

bool Dragon::eatableBy(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Dragon::eatableBy(A_Unused Food const *food) const {
    return false;
}

bool Dragon::matable(OrganicEntity const *other) const {
    return other->canMate(this);
}

bool Dragon::canMate(A_Unused Scorpion const *scorpion) const {
    return false;
}

bool Dragon::canMate(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Dragon::canMate(A_Unused Food const *food) const {
    return false;
}

bool Dragon::meet(OrganicEntity *mate) {
    return mate->meetManagement(this);
}

bool Dragon::meetManagement(A_Unused Scorpion *mate) {
    return false;
}

bool Dragon::meetManagement(A_Unused Gerbil *mate) {
    return false;
}

bool Dragon::meetManagement(A_Unused Food *mate) {
    return false;
}

double Dragon::getRandomWalkRadius() const {
    return getAppConfig().dragon_random_walk_radius;
}

double Dragon::getRandomWalkDistance() const {
    return getAppConfig().dragon_random_walk_distance;
}

double Dragon::getRandomWalkJitter() const {
    return getAppConfig().dragon_random_walk_jitter;
}

double Dragon::getSize() const {
    return getAppConfig().dragon_size;
}

double Dragon::getInitialEnergy() const {
    return getAppConfig().dragon_energy_initial;
}

double Dragon::getMinimumMatingEnergyMale() const {
    return getAppConfig().dragon_energy_min_mating_male;
}

double Dragon::getMinimumMatingEnergyFemale() const {
    return getAppConfig().dragon_energy_min_mating_female;
}

double Dragon::getMinimumMatingAge() const {
    return getAppConfig().dragon_min_age_mating;
}

const std::string Dragon::getTexturePath() const {
    if (animationTimer.asMilliseconds() < 250) {

        return getAppConfig().dragon_texture_d1;
    }
    if (animationTimer.asMilliseconds() < 500) {

        return getAppConfig().dragon_texture_d2;
    }
    if (animationTimer.asMilliseconds() < 750) {
        return getAppConfig().dragon_texture_d3;
    }
    return getAppConfig().dragon_texture_d4;
}

double Dragon::getEnergyLossFemalePerChild() const {
    return getAppConfig().dragon_energy_loss_female_per_child;
}

int Dragon::getMinimumNumberOfChildren() const {
    return getAppConfig().dragon_min_children;
}

int Dragon::getMaximumNumberOfChildren() const {
    return getAppConfig().dragon_max_children;
}

double Dragon::getGestationTimeConfig() const {
    return getAppConfig().dragon_gestation_time;
}

double Dragon::getEnergyLossMaleMatting() const {
    return getAppConfig().dragon_energy_loss_mating_male;
}

double Dragon::getStarvingEnergyLevel() const {
    return getAppConfig().dragon_energy_starving;
}

void Dragon::registerAnimalWithEnvironment() const {
    getAppEnv().incrementCounter(s::DRAGON);
}

void Dragon::removeAnimalWithEnvironment() const {
    getAppEnv().decrementCounter(s::DRAGON);
}

double Dragon::getEnergyLossFactor() const {
    return getAppConfig().dragon_energy_loss_factor;
}

Dragon::Dragon(const Vec2d &position, double energyLevel, bool isFemale): Animal(position,getSize(),energyLevel,isFemale) {
    registerAnimalWithEnvironment();
}

Dragon::Dragon(const Vec2d &position): Dragon(position,getInitialEnergy(), uniform(0,1) == 0) {}

Dragon::~Dragon() {
    removeAnimalWithEnvironment();
}

bool Dragon::eatableBy(A_Unused Dragon const *dragon) const {
    return false;
}

bool Dragon::canMate(Dragon const *dragon) const {
    return Animal::canMate(dragon);
}

bool Dragon::meetManagement(Dragon *mate) {
    procreate();
    mate->procreate();
    return true;
}

void Dragon::update(sf::Time dt) {
    Animal::update(dt);
    spriteFireTimer += dt;

    if (animationTimer.asMilliseconds() > 1000) {
        animationTimer = sf::Time::Zero;
    }
    if(getState() != GIVING_BIRTH && getState() != MATING)
        animationTimer += dt;
    if(getAppEnv().isDragonFireTrigger()) {
        spriteFireTimer = sf::Time::Zero;
    }if(spriteFireTimer.asMilliseconds()>1100&& spriteFireTimer.asMilliseconds()<2600){
        spitFire();
    }
}

bool Dragon::giveBirth() {
    if(Animal::giveBirth()){
        for(int i(0); i < getNumberOfChildren(); i++){
            getAppEnv().addEntity(new Dragon(getPosition()));
        }
        return true;
    }
    return false;
}

void Dragon::draw(sf::RenderTarget &targetWindow) const {
    Animal::draw(targetWindow);


    if(spriteFireTimer.asMilliseconds() > 1100 && spriteFireTimer.asMilliseconds() < 2600) {
        sf::Texture &texture = getAppTexture(getAppConfig().dragon_fire_d1);
        int nbMillisecond = spriteFireTimer.asMilliseconds();
        if(nbMillisecond < 1475 )
            texture = getAppTexture(getAppConfig().dragon_fire_d1);
        else if(nbMillisecond < 1950)
            texture = getAppTexture(getAppConfig().dragon_fire_d2);
        else if(nbMillisecond < 2370)
            texture = getAppTexture(getAppConfig().dragon_fire_d3);
        else
            texture = getAppTexture(getAppConfig().dragon_fire_d4);

        auto image_to_draw(buildSprite(convertToGlobalCoord(Vec2d(100,0)), 100, texture, getRotation() / DEG_TO_RAD));
        targetWindow.draw(image_to_draw);
    }
}

bool Dragon::isTargetInBurnRange(const Vec2d &target) const {
    Vec2d d = target - getPosition();
    if (d.lengthSquared() <= getAppConfig().dragon_burn_distance * getAppConfig().dragon_burn_distance) {
        Vec2d this_to_target = target - getPosition();
        double length = this_to_target.lengthSquared();
        if (isEqual(length, 0)) {
            return true;
        }
        this_to_target = this_to_target.normalised();
        return getDirection().dot(this_to_target) >= cos((getAppConfig().dragon_burn_range + 0.001) / 2);
    }
    return false;
}

void Dragon::spitFire() const {
    std::list<OrganicEntity*> burnList = getAppEnv().getEntitiesInBurnRangeOfDragon(this);
    for (auto &i : burnList) {
        if(i->isBurnable())
            i->spendEnergy(10000);
    }
}

bool Dragon::isBurnable() {
    return false;
}



