//
// Created by jeremy on 3/11/19.
//

#ifndef INFOSV_CIRCULARCOLLIDER_HPP
#define INFOSV_CIRCULARCOLLIDER_HPP


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
    Vec2d& clamp(Vec2d const& cord);
public:

    /*!
     * Creates a circular collider but ensures that the position is inside the toric world.
     * @param position
     * @param radius of the collider collision detection with this obj.
     *
     * @throw Fatal exception if radius is negative.
     */
    CircularCollider(const Vec2d &position, double radius);

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

    Vec2d directionTo(Vec2d const& ) const;

    Vec2d directionTo(CircularCollider const& ) const;

};


#endif //INFOSV_CIRCULARCOLLIDER_HPP
