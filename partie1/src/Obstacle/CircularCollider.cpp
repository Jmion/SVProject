//
// Created by jeremy on 3/11/19.
//

#include "CircularCollider.hpp"

const Vec2d &CircularCollider::getPosition() const {
    return position;
}

void CircularCollider::setPosition(const Vec2d &position) {
    CircularCollider::position = position;
}

double CircularCollider::getRadius() const {
    return radius;
}

void CircularCollider::setRadius(double radius) {
    CircularCollider::radius = radius;
}

CircularCollider::CircularCollider(const Vec2d &position, double radius) : position(position), radius(radius) {}
