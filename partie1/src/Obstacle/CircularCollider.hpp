//
// Created by jeremy on 3/11/19.
//

/*!
 * \brief
 */

#ifndef INFOSV_CIRCULARCOLLIDER_HPP
#define INFOSV_CIRCULARCOLLIDER_HPP

#include "../Utility/Vec2d.hpp"
#include <iostream>

class CircularCollider {
private:
    Vec2d position; // position of center
    double radius;

    /*!
     * Clamps the coordinates inside the toric world.
     *
     * If the coordinates are outside the width / height of the world
     * there coordinates will be readjusted to within the world by adding or subracting
     * the width / height, to the x /y coordinate respectively
     *
     * As long as the x cord is inferior to zero
     *
     * @param cord that will be modified.
     */
    Vec2d& clamp(Vec2d& cord);

public:

    /*!
     * Creates a circular collider but ensures that the position is inside the toric world.
     * @param position
     * @param radius of the collider collision detection with this obj.
     *
     * @throw Fatal exception if radius is negative.
     */
    CircularCollider(Vec2d position, double radius);

    /*!
     * Gets the current position of the collider
     * @return the position of the collider
     */
    const Vec2d& getPosition() const;

    /*!
     * The radius of the collider.
     * @return the radius of the collider
     */
    double getRadius() const;

    /*!
     * Default copy constructor will go a surface copy of the attributes.
     */
    CircularCollider(const CircularCollider&) = default;

    /*!
     * Will do a surface copy of the attributes.
     * @return
     */
    CircularCollider &operator=(const CircularCollider &) = default;

    /*!
     * Calculates the smalest vector to get from <i>from<\i> to <i>to<\i>
     * @param to the destination
     * @return The smalest vector that will allow to go from "from" to "to"
     */
    Vec2d directionTo(const Vec2d & to) const;

    /*!
     *
     * @see directionTo
     * @param to destination of the vector
     * @return
     */
    Vec2d directionTo(const CircularCollider & to) const;

    double distanceTo(const Vec2d&) const;

    double distanceTo(const CircularCollider&) const;

    Vec2d& move(const Vec2d&);

    CircularCollider& operator+=(const Vec2d&);

    /*!
     * Will check whether other is inside this. In case where they are touching at
     * the edge it is still constidered inidee.
     * @param other circular collider
     * @return true if other is inside this. Otherwise returns false
     */
    bool isCircularColliderInside(const CircularCollider& other) const;

    /*!
     * Determins is there is a collision between this and other
     * @param other CircularCollider involved in the collision check
     * @return true is collision is occuring. false otherwise
     */
    bool isColliding(const CircularCollider& other) const;

    /*!
     * Determins if the point p is inside the cirucularCollider
     * @param p the point to check
     * @return true if p is inside this
     */
    bool isPointInside(const Vec2d& p) const;

    /*!
     * @param other circular collider
     * @return true if other is inside this, otherwise false.
     */
    bool operator>(const CircularCollider& other) const;

    /*!
     *
     * @param other circular collider
     * @return true if other is colliding with this
     */
    bool operator|(const CircularCollider& other) const;

    /*!
     *
     * @param point
     * @return true if point is inside this circullar body. otherwise false
     */
    bool operator>(const Vec2d& point);


};
std::ostream& operator<<(std::ostream&, CircularCollider const&);


#endif //INFOSV_CIRCULARCOLLIDER_HPP
