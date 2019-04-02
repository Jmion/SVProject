//
// Created by jeremy on 4/2/19.
//

#include "Food.hpp"
#include <Application.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Utility/Utility.hpp>


void Food::draw(sf::RenderTarget &target) const {
    sf::Texture& texture = getAppTexture(getTexturePath());
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture));
    target.draw(image_to_draw);
}

void Food::update(sf::Time dt) {

}

Food::Food(const Vec2d &position) :OrganicEntity(position,getSize(),getEnergy()){

}

double Food::getSize() const {
    return getAppConfig().food_size;
}

double Food::getEnergy() const {
    return getAppConfig().food_energy;
}

std::string Food::getTexturePath() const {
    return getAppConfig().food_texture;
}
