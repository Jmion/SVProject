//
// Created by jeremy on 4/30/19.
//

#include <Application.hpp>
#include "Wave.hpp"
#include <Utility/Arc.hpp>
#include <cmath>
#include <Obstacle/SolideObstacle.hpp>

Wave::Wave(const Vec2d &position, double initialEnergy, double radius, double mu, double speed) :
    CircularCollider(position, radius),
    arcs(),
    initialEnergy(initialEnergy),
    mu(mu),
    speed(speed),
    collidedWith()
{
    arcs.emplace_back(-PI, PI);
}

double Wave::getEnergy() const
{
    return initialEnergy * exp(-getRadius() / mu);
}

double Wave::getIntensity() const
{
    return getEnergy() / (2 * PI * getRadius());
}

void Wave::draw(sf::RenderTarget &target) const
{
    for (auto &p : arcs) {
        Arc arc(p.first / DEG_TO_RAD, p.second / DEG_TO_RAD, getRadius(), sf::Color::Black, getIntensity());
        arc.setOrigin(getRadius(), getRadius());
        arc.setPosition(getPosition());
        target.draw(arc);
    }
}

void Wave::update(sf::Time dt)
{
    setRadius(dt.asSeconds() * getAppConfig().wave_default_speed + getRadius());

    //Wave splitting of rock
    std::list<SolideObstacle *> solideObstacles = getAppEnv().getSolideObstaclesCollidingForWave(this);
    for (SolideObstacle *s: solideObstacles) {
        if (s != nullptr && collidedWith.find(s) == collidedWith.end()) {
            Vec2d direction = directionTo(*s);
            double beta = direction.angle();
            double halfAlpha = atan2(s->getRadius(), direction.length() + s->getRadius());
            std::pair<double, double> arcToAdd;
            bool arcCollidedWithObstacle = false;
            for (auto &a: arcs) {
                if (a.first < beta - halfAlpha && a.second > beta + halfAlpha) {
                    arcToAdd.second = a.second;
                    a.second = beta - halfAlpha;
                    arcToAdd.first = beta + halfAlpha;
                    if (arcToAdd.first < arcToAdd.second) {
                        arcs.push_back(arcToAdd);
                        arcCollidedWithObstacle = true;
                    }
                }
            }
            if (arcCollidedWithObstacle)
                collidedWith.insert(s);
        }
    }
}

bool Wave::isWaveToBeDeleted()
{
    return getIntensity() < getAppConfig().wave_intensity_threshold;
}

bool Wave::isPointWithinArcs(const Vec2d &vec2D)
{
    double angleOfTarget = (vec2D - getPosition()).angle();
    for (auto &a : arcs) {
        if (angleOfTarget >= a.first && angleOfTarget <= a.second)
            return true;
    }
    return false;
}



