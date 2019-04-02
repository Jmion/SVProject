//
// Created by jeremy on 4/1/19.
//

#ifndef PARTIE1_ORGANICENTITY_HPP
#define PARTIE1_ORGANICENTITY_HPP

#include <Obstacle/CircularCollider.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class OrganicEntity : public CircularCollider, public Drawable, public Updatable{
public:
    /*!
     * Creates an organic entity
     * @param position that the organic entity will be placed initially
     * @param size of the organic entity (diameter of the organic entity) The collider ascociated to this shape is 1/2 of size
     * @param energyLevel of the organic entity.
     */
    OrganicEntity(const Vec2d& position, double size, double energyLevel);


private:

    /*!
     * Energy level of the animal
     */
    double  energyLevel;

};


#endif //PARTIE1_ORGANICENTITY_HPP
