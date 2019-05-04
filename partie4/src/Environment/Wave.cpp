//
// Created by jeremy on 4/30/19.
//

#include <Application.hpp>
#include "Wave.hpp"
#include <Utility/Arc.hpp>
#include <cmath>
#include <Obstacle/SolideObstacle.hpp>

Wave::Wave(const Vec2d &position, double initialEnergy, double radius, double mu,double speed):
        CircularCollider(position, radius),
        arcs(),
        initialEnergy(initialEnergy),
        mu(mu),
        speed(speed){
    arcs.emplace_back(-PI,PI);
}

double Wave::getEnergy() const{
    return initialEnergy*exp(-getRadius()/mu);
}

double Wave::getIntensity() const{
    return getEnergy()/(2*PI*getRadius());
}

void Wave::draw(sf::RenderTarget &target) const {
    for (auto &p : arcs) {
        Arc arc(p.first/DEG_TO_RAD,p.second/DEG_TO_RAD,getRadius(),sf::Color::Black,getIntensity());
        arc.setOrigin(getRadius(), getRadius());
        arc.setPosition(getPosition());
        target.draw(arc);
    }
}

void Wave::update(sf::Time dt) {
    setRadius(dt.asSeconds()*getAppConfig().wave_default_speed+getRadius());

    //Wave splitting of rock
    std::list<SolideObstacle*> solideObstacles = getAppEnv().getSolideObstaclesCollidingForWave(this);
    for (SolideObstacle* s: solideObstacles) {
        if (s != nullptr) {
            Vec2d direction = directionTo(*s);
            double halfAlpha = atan2(s->getRadius(),direction.length()+s->getRadius());
            double beta = direction.angle();
            std::pair<double,double> arcToAdd;
            for (auto &a: arcs) {
                if(a.first< beta && a.second >beta){
                    arcToAdd.second = a.second;
                    a.second = beta-halfAlpha;
                    arcToAdd.first = beta + halfAlpha;
                    if (arcToAdd.first < arcToAdd.second) {
                        arcs.push_back(arcToAdd);
                    }
                }
            }

        }
    }
}

bool Wave::isWaveToBeDeleted() {
        return getIntensity() < getAppConfig().wave_intensity_threshold;
}



