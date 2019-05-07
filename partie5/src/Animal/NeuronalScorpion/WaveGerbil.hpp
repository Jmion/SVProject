//
// Created by jeremy on 5/4/19.
//

#ifndef PARTIE1_WAVEGERBIL_HPP
#define PARTIE1_WAVEGERBIL_HPP

#include <Animal/Gerbil.hpp>
class WaveGerbil : public Gerbil{
private:
    /*!
     * Time since the Gerbil last emited a Wave
     */
    sf::Time timeSinceLastWave = sf::Time::Zero;
public:
    void update(sf::Time dt) override;
    using Gerbil::Gerbil;
    void draw(sf::RenderTarget &targetWindow) const override;
};


#endif //PARTIE1_WAVEGERBIL_HPP
