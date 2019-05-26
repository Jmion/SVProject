//
// Created by jeremy on 5/2/19.
//

#ifndef PARTIE1_SOLIDEOBSTACLE_HPP
#define PARTIE1_SOLIDEOBSTACLE_HPP


#include "CircularCollider.hpp"

class SolideObstacle : public CircularCollider
{
private:
    /*!
     * Orientation of the rock in 3D space.
     * Angle is in radians
     */
    double rotation;

    double getRotation() const;


public:
    /*!
     * Creates a solide Obstacle
     * @param postion of the obstacle
     * @param radius of the obstacle
     * @param angle orientation of the obstacle
     */
    SolideObstacle(const Vec2d &postion, const double radius, const double angle);

    virtual ~SolideObstacle() = default;

protected:

    virtual std::string getTexturePath() const  = 0;

public:
    void draw(sf::RenderTarget &target) const override;
};


#endif //PARTIE1_SOLIDEOBSTACLE_HPP
