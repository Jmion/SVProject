//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_GERBIL_HPP
#define PARTIE1_GERBIL_HPP

#include <Animal/Animal.hpp>

class Gerbil : public Animal
{
public:

    /*!
     * Builds a Gerbil and positions it at the given position. The sex is determined by the value of the parameter
     * isFemale and the initial energy level of the animal is set with the initial energy parameter
     * @param position where the Gerbil will appear
     * @param energyLevel at the spawn moment
     * @param isFemale if true the gerbil will be a female, else it will be a male
     */
    Gerbil(const Vec2d &position, double energyLevel, bool isFemale);


    /*!
     * This creates a gerbil, with a default energy level as defined in the config JSON file.
     * The gerbil created has a 50% chance of being a male and 50% female.
     * @param position where the Gerbil will appear.
     */
    explicit Gerbil(const Vec2d &position);

    double getStandardMaxSpeed() const override;

    double getMass() const override;

    double getViewRange() const override;

    double getViewDistance() const override;

    ~Gerbil() override;

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

    bool meetManagement(Gerbil *mate) override;

    bool meetManagement(Scorpion *mate) override;

    bool meetManagement(Food *mate) override;

    bool meetManagement(Dragon *mate) override;

protected:
    double getEnergyLossFemalePerChild() const override;

    int getMinimumNumberOfChildren() const override;

    int getMaximumNumberOfChildren() const override;

    double getGestationTimeConfig() const override;

    double getEnergyLossMaleMatting() const override;

    void registerAnimalWithEnvironment() const;

    void removeAnimalWithEnvironment() const;

    double getRandomWalkRadius() const override;

    double getRandomWalkDistance() const override;

    double getRandomWalkJitter() const override;

    double getSize() const override;

    double getInitialEnergy() const override;

    const std::string getTexturePath() const override;

    double getMinimumMatingEnergyMale() const override;

    double getMinimumMatingEnergyFemale() const override;

    double getMinimumMatingAge() const override;

private:
    sf::Time getLongevity() const override;

    double getStarvingEnergyLevel() const override;

    double getEnergyLossFactor() const override;

    bool giveBirth() override;
};


#endif //PARTIE1_GERBIL_HPP
