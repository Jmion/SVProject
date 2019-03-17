//
// Created by jeremy on 3/17/19.
//

#include "ChasingAutomaton.hpp"


double ChasingAutomaton::getMass() const{
    return CHASING_AUTOMATON_MASS;
}

double ChasingAutomaton::getStandardMaxSpeed() const {
    return CHASING_AUTOMATON_MAX_SPEED;
}

ChasingAutomaton& ChasingAutomaton::setTargetPosition(const Vec2d &target) {
    targetPosition = target;
    return *this;
}

Vec2d ChasingAutomaton::getSpeedVector() const {
    return direction*speed;
}

ChasingAutomaton::ChasingAutomaton(Vec2d _postion): CircularCollider(_postion,CHASING_AUTOMATON_RADIUS), speed(0), targetPosition(Vec2d(0,0)), direction(Vec2d(0,0)) {}

void ChasingAutomaton::update(sf::Time dt) {
    //TODO
}

void ChasingAutomaton::draw(sf::RenderTarget &targetWindow) {

}