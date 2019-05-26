//
// Created by jeremy on 5/13/19.
//

#ifndef PARTIE1_DRAGON_HPP
#define PARTIE1_DRAGON_HPP


#include "Animal.hpp"
#include <SFML/Audio.hpp>

class Dragon : public Animal {

public:

    Dragon(const Vec2d &position, double energyLevel, bool isFemale);

    explicit Dragon(const Vec2d &position);

    ~Dragon();

    void update(sf::Time dt) override;

    double getStandardMaxSpeed() const override;

    double getMass() const override;

    double getViewRange() const override;

    double getViewDistance() const override;

    bool eatable(OrganicEntity const *entity) const override;

    bool eatableBy(Scorpion const *scorpion) const override;

    bool eatableBy(Gerbil const *gerbil) const override;

    bool eatableBy(Food const *food) const override;

    bool eatableBy(Dragon const *dragon) const override;

    bool matable(OrganicEntity const *other) const override;

    bool canMate(Scorpion const *scorpion) const override;

    bool canMate(Gerbil const *gerbil) const override;

    bool canMate(Food const *food) const override;

    bool canMate(Dragon const *dragon) const override;

    bool meet(OrganicEntity *mate) override;

    bool meetManagement(Scorpion *mate) override;

    bool meetManagement(Gerbil *mate) override;

    bool meetManagement(Food *mate) override;

    bool meetManagement(Dragon *mate) override;

    /*!
     * Will determine if the target can be burnt by the Dragon
     * @param target that needs to be tested if it can be burnt
     * @return true if target can be burnt by the animal, false otherwise
     */
    bool isTargetInBurnRange(const Vec2d &target) const;

protected:
    double getRandomWalkRadius() const override;

    double getRandomWalkDistance() const override;

    double getRandomWalkJitter() const override;

    double getSize() const override;

    double getInitialEnergy() const override;

    double getMinimumMatingEnergyMale() const override;

    double getMinimumMatingEnergyFemale() const override;

    double getMinimumMatingAge() const override;

    const std::string getTexturePath() const override;

    double getEnergyLossFemalePerChild() const override;

    int getMinimumNumberOfChildren() const override;

    int getMaximumNumberOfChildren() const override;

    double getGestationTimeConfig() const override;

    double getEnergyLossMaleMatting() const override;

    double getStarvingEnergyLevel() const override;

    bool giveBirth() override;

    bool isBurnable() override;

public:
    void draw(sf::RenderTarget &targetWindow) const override;

private:

    /*!
     * Time since last full animation cycle
     */
    sf::Time animationTimer = sf::Time::Zero;

    /*!
     * Time since start of fireball
     */
    sf::Time spriteFireTimer = sf::seconds(500);

    void registerAnimalWithEnvironment() const;

    void removeAnimalWithEnvironment() const;

    double getEnergyLossFactor() const override;

    void spitFire() const;


};


#endif //PARTIE1_DRAGON_HPP
