//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_GERBIL_HPP
#define PARTIE1_GERBIL_HPP

#include <Animal/Animal.hpp>

class Gerbil : public Animal{
public:

    /*!
     * Builds a Gerbil and positions it at the given position. The sex is determined by the value of the parameter
     * isFemale and the initial energy level of the animal is set with the initial energy parameter
     * @param position where the Gerbil will appear
     * @param energyLevel at the spawn moment
     * @param isFemale if true the gerbil will be a female, else it will be a male
     */
    Gerbil(const Vec2d& position, double energyLevel, bool isFemale);



    /*!
     * This creates a gerbil, with a default energy level as defined in the config JSON file.
     * The gerbil created has a 50% chance of being a male and 50% female.
     * @param position where the Gerbil will appear.
     */
    explicit Gerbil(const Vec2d& position);
    //TODO ask about making parrent method explcit

    double getStandardMaxSpeed() const override;

    double getMass() const override;

    double getViewRange() const override;

    double getViewDistance() const override;

    ~Gerbil() override;

protected:
    double getRandomWalkRadius() const override;

    double getRandomWalkDistance() const override;

    double getRandomWalkJitter() const override;

    double getSize() const override;

    double getInitialEnergy() const override;

    const std::string getTexturePath() const override;
};


#endif //PARTIE1_GERBIL_HPP
