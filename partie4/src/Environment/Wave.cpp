//
// Created by jeremy on 4/30/19.
//

#include <Application.hpp>
#include "Wave.hpp"
#include <Utility/Arc.hpp>

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
}

bool Wave::isWaveToBeDeleted() {
        return getIntensity() < getAppConfig().wave_intensity_threshold;
    }
}


