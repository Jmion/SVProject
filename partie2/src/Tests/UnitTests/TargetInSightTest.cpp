/*
* prjsv 2016
* 2016
* Marco Antognini
*/

#include <Application.hpp>
#include <Animal/Animal.hpp>
#include <Utility/Constants.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <iostream>
#define STEP 2

#if STEP >= 3
#include <Environment/OrganicEntity.hpp>
#include <Environment/Food.hpp>
#include <Animal/Scorpion.hpp>
#include <Animal/Gerbil.hpp>
#endif

class DummyAnimal : public Animal
{
public:
    DummyAnimal(Vec2d const& position,
                Vec2d const& heading)
#if STEP >= 3
        : Animal(position, 0, 0, false)
#else
        : Animal(position)
#endif
    {
        setHeading(heading);
    }

    // Break encapsulation for this test
    void setHeading(Vec2d const& heading)
    {
        setRotation(heading.angle());
    }

    static constexpr double ANIMAL_VIEW_DISTANCE = 300;
    static constexpr double ANIMAL_VIEW_RANGE =  1.04719755; // =60 * DEG_TO_RAD;
#if STEP ==2
    double getViewRange() const
    {
        return ANIMAL_VIEW_RANGE;
    }

    double getViewDistance() const
    {
        return ANIMAL_VIEW_DISTANCE;
    }
#endif
#if STEP >= 3
    double getViewRange() const override
    {
        return ANIMAL_VIEW_RANGE;
    }

    double getViewDistance() const override
    {
        return ANIMAL_VIEW_DISTANCE;
    }

    bool eatable(const OrganicEntity*) const override
    {
        return false;
    }
    bool eatableDispatch(const Scorpion*) const override
    {
        return false;
    }
    bool eatableDispatch(const Gerbil*) const override
    {
        return false;
    }
    bool eatableDispatch(const Food*) const override
    {
        return false;
    }
    bool matable(const OrganicEntity*) const  override
    {
        return false;
    }
    bool matableDispatch(const Scorpion*) const override
    {
        return false;
    }
    bool matableDispatch(const Gerbil*) const override
    {
        return false;
    }
    bool matableDispatch(const Food*) const override
    {
        return false;
    }

    void meet(OrganicEntity*)  override
    {
        /* does nothing */
    }
    void meetDispatch(Scorpion*) override
    {
        /* does nothing */
    }
    void meetDispatch(Gerbil*) override
    {
        /* does nothing */
    }
    void meetDispatch (Food*) override
    {
        /* does nothing */
    }
    double getStandardMaxSpeed() const override
    {
        return 0.;
    }
    double getMass() const override
    {
        return 0.;
    }
    double getEnergyLostFactor() const override
    {
        return 0.;
    }

    double getRandomWalkJitter() const override
    {
        return 0.;
    }
    double getRandomWalkRadius() const override
    {
        return 0.;
    }

    double getRandomWalkDistance() const override
    {
        return 0.;
    }

    void giveBirth(unsigned int)
    {
        /*does nothing */
    }
#endif
};

// Utility function
// angle in radian, considered radius is abs(radius)
Vec2d Polar2Cartesian(double angle, double radius)
{
    return std::abs(radius) * Vec2d(std::cos(angle), std::sin(angle));
}


SCENARIO("Animal interacts with target", "[Animal]")
{

    const Vec2d  initialPosition(100, 100);
    const Vec2d initialOrientation(1, 0);
    Vec2d target(initialPosition);
    DummyAnimal animal(initialPosition, initialOrientation);
    double const viewDistance(animal.getViewDistance()); // angle de vue
    double const viewRange(animal.getViewRange()); // distance de visibilité


    GIVEN("A target at the same position as the animal") {
        THEN("the target is seen by animal") {
            CHECK(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target in the field of view of the animal") {

        target = initialPosition +
                 initialOrientation * viewDistance / 2;

        THEN("the target is seen by the animal") {
            CHECK(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target close to the animal, on the borders of its view range") {

        target = animal.getPosition() + Polar2Cartesian(viewRange / 2, 1);

        THEN("the target is seen by the animal") {
            CHECK(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target in the view range of the animal, at the upper limits of its view distance") {
        target = animal.getPosition() + initialOrientation * viewDistance;


        THEN("the target is seen by the animal") {
            CHECK(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target in the view range of the animal but too distant") {

        target = animal.getPosition() + initialOrientation * (viewDistance + 1);


        THEN("the target is not seen by the animal") {
            CHECK_FALSE(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target in the view range of the animal but too distant") {

        target = animal.getPosition() + initialOrientation * (viewDistance + 1);


        THEN("the target is not seen by the animal") {
            CHECK_FALSE(animal.isTargetInSight(target));
        }
    }

    GIVEN("A target close to the animal but outside its view range") {
        target = animal.getPosition() + Polar2Cartesian((viewRange + 1) / 2, 2);

        THEN("the target is not seen by the animal") {
            CHECK_FALSE(animal.isTargetInSight(target));
        }
    }

    GIVEN("A new orientation of the animal and a target outside its view field") {
        const Vec2d newOrientation = Polar2Cartesian(31 * DEG_TO_RAD, 1);
        // "Oriente l'animal à 31°:
        animal.setHeading(newOrientation);
        // Repositionne la cible sur l'abscisse, donc hors du champs de vision
        target = initialPosition + initialOrientation * 2;

        THEN("the target is not seen by the animal") {
            CHECK_FALSE(animal.isTargetInSight(target));
        }
    }

    GIVEN("A new orientation of the animal and a target inside its view field") {
        const Vec2d newOrientation = Polar2Cartesian(31 * DEG_TO_RAD, 1);

        // "Oriente l'animal à 31°:
        animal.setHeading(newOrientation);

        //Création d'une cible en face de l'animal:
        target =  initialPosition + newOrientation * 2;

        THEN("the target is seen by the animal") {
            CHECK(animal.isTargetInSight(target));
        }
    }
}
