//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_SCORPION_HPP
#define PARTIE1_SCORPION_HPP

#include <Animal/Animal.hpp>

class Scorpion : public Animal{

public:

    Scorpion(const Vec2d& position, double energyLevel, bool isFemale);

    explicit Scorpion(const Vec2d& position);

    double getStandardMaxSpeed() const override;

    double getMass() const override;

    double getViewRange() const override;

    double getViewDistance() const override;

protected:
    double getRandomWalkRadius() const override;

    double getRandomWalkDistance() const override;

    double getRandomWalkJitter() const override;

    const std::string getTexturePath() const override;

public:
    ~Scorpion() override;

protected:
    double getSize() const override;

    double getInitialEnergy() const override;
};


#endif //PARTIE1_SCORPION_HPP
