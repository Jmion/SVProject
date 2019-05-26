//
// Created by jeremy on 5/4/19.
//

#include <Application.hpp>
#include "WaveGerbil.hpp"
#include <Environment/Wave.hpp>
#include <Animal/Animal.hpp>

void WaveGerbil::update(sf::Time dt) {
    Animal::update(dt);
    timeSinceLastWave += dt;
    if (timeSinceLastWave.asSeconds() > 1 / getAppConfig().wave_gerbil_frequency) {
        getAppEnv().addWave(new Wave(
                getPosition(),
                getAppConfig().wave_default_energy,
                getAppConfig().wave_default_radius,
                getAppConfig().wave_default_mu,
                getAppConfig().wave_default_speed));
        timeSinceLastWave = sf::Time::Zero;
    }
}

void WaveGerbil::draw(sf::RenderTarget &targetWindow) const {
    Animal::draw(targetWindow);
    if (isDebugOn()) {
        auto text = buildText("frequency" + to_nice_string(getAppConfig().wave_gerbil_frequency),
                              convertToGlobalCoord(Vec2d(30, 0)), getAppFont(),
                              getAppConfig().default_debug_text_size,
                              sf::Color::Black, getRotation() / DEG_TO_RAD + 90);
        targetWindow.draw(text);
    }
}


