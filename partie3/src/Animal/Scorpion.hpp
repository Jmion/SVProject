//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_SCORPION_HPP
#define PARTIE1_SCORPION_HPP

#include <Animal/Animal.hpp>

class Scorpion : public Animal
{


public:

    Scorpion(const Vec2d& position, double energyLevel, bool isFemale);

    explicit Scorpion(const Vec2d& position);

    double getStandardMaxSpeed() const override;

    double getMass() const override;

    double getViewRange() const override;

    double getViewDistance() const override;

    ~Scorpion() override;

    bool eatable(OrganicEntity const *entity) const override;

    bool eatableBy(Scorpion const *scorpion) const override;

    bool eatableBy(Gerbil const *gerbil) const override;

    bool eatableBy(Food const *food) const override;

    bool meet(OrganicEntity *mate) override;

    bool meetManagement(Scorpion *mate) override;

    bool meetManagement(Gerbil *mate) override;

    bool meetManagement(Food *mate) override;

protected:
    double getEnergyLossFemalePerChild() const override;

    int getMinimumNumberOfChildren() const override;

    int getMaximumNumberOfChildren() const override;

    double getGestationTimeConfig() const override;

    double getEnergyLossMaleMatting() const override;


protected:
    double getRandomWalkRadius() const override;

    double getRandomWalkDistance() const override;

    double getRandomWalkJitter() const override;

    const std::string getTexturePath() const override;

    double getSize() const override;

    double getInitialEnergy() const override;

private:
    sf::Time getLongevity() const override;

    double getEnergyLossFactor() const override;

public:
    bool matable(OrganicEntity const *other) const override;

    bool canMate(Scorpion const *scorpion) const override;

    bool canMate(Gerbil const *gerbil) const override;

    bool canMate(Food const *food) const override;

protected:
    double getMinimumMatingEnergyMale() const override;

    double getMinimumMatingEnergyFemale() const override;

    double getMinimumMatingAge() const override;

private:
    double getStarvingEnergyLevel() const override;

protected:
    bool giveBirth() override;
};


#endif //PARTIE1_SCORPION_HPP
