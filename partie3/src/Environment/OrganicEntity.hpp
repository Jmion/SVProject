//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_ORGANICENTITY_HPP
#define PARTIE1_ORGANICENTITY_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
class Scorpion;
class Gerbil;
class Food;


class OrganicEntity : public CircularCollider, public Updatable{
public:
    /*!
     * Creates an organic entity
     * @param position that the organic entity will be placed initially
     * @param size of the organic entity (diameter of the organic entity) The collider ascociated to this shape is 1/2 of size
     * @param energyLevel of the organic entity.
     */
    OrganicEntity(const Vec2d& position, double size, double energyLevel);


    /*!
     * Determins if entity is eatable.
     *
     * To achive this this methode uses double dispatche. It will call the methode eatableBy.
     * This allows the management of how can eat each animal up to itself. this is usefull
     * because it gives the management to the animal itself
     * @param entity that we want to know if this can eat
     * @return true if it is eatable
     */
    virtual bool eatable(OrganicEntity const* entity) const = 0;





    /*!
    * Determins if this can be eaten by a scorpion.
    */
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;
    /*!
     * Determins if this can be eaten by a gerbil.
     */
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    /*!
     * Determins if this can be eaten by a food.
     */
    virtual bool eatableBy(Food const* food) const = 0;

    double getEngeryLevel() const;


private:
    /*!
     * Energy level of the animal
     */
    double  energyLevel;

};


#endif //PARTIE1_ORGANICENTITY_HPP
