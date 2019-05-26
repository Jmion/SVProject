//
// Created by jeremy on 3/11/19.
//

#include "CircularCollider.hpp"
#include <Application.hpp>
#include <cfloat>
#include <cmath>
#include "../Utility/Vec2d.hpp"
#include <Utility/Utility.hpp>


const Vec2d& CircularCollider::getPosition() const
{
    return position;
}

double CircularCollider::getRadius() const
{
    return radius;
}

CircularCollider::CircularCollider(Vec2d position, double radius) : radius(radius)
{
    if(radius<0)
        throw std::invalid_argument("Radius is negative.");
    this->position = clamp(position);
}

Vec2d& CircularCollider::clamp(Vec2d& cord)
{
    auto worldSize = getAppConfig().simulation_world_size;
    while(cord.x<0) {
        cord.x += worldSize;
    }
    while(cord.x>=worldSize) {
        cord.x -= worldSize;
    }
    while(cord.y<0) {
        cord.y += worldSize;
    }
    while(cord.y>= worldSize) {
        cord.y -= worldSize;
    }
    return cord;
}


Vec2d CircularCollider::directionTo(const Vec2d & to) const
{
    double minDist(DBL_MAX);
    Vec2d smalestMove;
    auto worldSize = getAppConfig().simulation_world_size;

    for(int i(-1); i<= 1; i++) {
        for(int j(-1); j<= 1; j++) {
            Vec2d nTo(to.x+worldSize*i,to.y+worldSize*j);
            double tempDistance(distance(position,nTo));
            if(tempDistance<minDist) {
                smalestMove = nTo-position;
                minDist = tempDistance;
            }
        }
    }
    return smalestMove;
}

Vec2d CircularCollider::directionTo(CircularCollider const& collider) const
{
    return directionTo(collider.position);
}

double CircularCollider::distanceTo(const Vec2d& v) const
{
    return directionTo(v).length();
}

double CircularCollider::distanceTo(const CircularCollider& collider) const
{
    return distanceTo(collider.position);
}

CircularCollider& CircularCollider::move(const Vec2d & dx)
{
    Vec2d temp(position + dx);
    position = clamp(temp);
    return *this;
}

CircularCollider& CircularCollider::operator+=(const Vec2d & dx)
{
    move(dx);
    return *this;
}

bool CircularCollider::isCircularColliderInside(const CircularCollider &other) const
{
    return other.radius<= radius && distanceTo(other)<=fabs((other.radius-radius));
}

bool CircularCollider::isColliding(const CircularCollider &other) const
{
    return (radius + other.radius) >= distanceTo(other);
}

bool CircularCollider::isPointInside(const Vec2d &p) const
{
    return radius>= distanceTo(p);
}

bool CircularCollider::operator>(const CircularCollider &other) const
{
    return isCircularColliderInside(other);
}

bool CircularCollider::operator|(const CircularCollider &other) const
{
    return isColliding(other);
}

bool CircularCollider::operator>(const Vec2d &point) const
{
    return isPointInside(point);
}

void CircularCollider::draw(sf::RenderTarget &target) const
{
    if(isDebugOn()) {
        sf::CircleShape circle = buildCircle(getPosition(), getRadius(), sf::Color::White);
        target.draw(circle);
    }
}

void CircularCollider::setRadius(double radius)
{
    this->radius = radius;
}


std::ostream& operator<<(std::ostream & out, CircularCollider const & collider)
{
    out << "CircularCollider: position = " << collider.getPosition() << " radius = " << collider.getRadius();
    return out;
}
