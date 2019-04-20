//
// Created by jeremy on 4/2/19.
//

#include "Food.hpp"
#include <Application.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Macros.hpp>


void Food::draw(sf::RenderTarget &target) const
{
    CircularCollider::draw(target);
    sf::Texture& texture = getAppTexture(getTexturePath());
    auto image_to_draw(buildSprite(getPosition(),getRadius()*2,texture));
    target.draw(image_to_draw);
}

void Food::update(sf::Time dt)
{

}

Food::Food(const Vec2d &position) :OrganicEntity(position,getSize(),getEnergy())
{

}

double Food::getSize() const
{
    return getAppConfig().food_size;
}

double Food::getEnergy() const
{
    return getAppConfig().food_energy;
}

std::string Food::getTexturePath() const
{
    return getAppConfig().food_texture;
}

bool Food::eatable(OrganicEntity const *entity) const
{
    return entity->eatableBy(this);
}

bool Food::eatableBy(A_Unused Scorpion const *scorpion) const
{
    return false;
}

bool Food::eatableBy(A_Unused Gerbil const *gerbil) const
{
    return true;
}

bool Food::eatableBy(A_Unused Food const *food) const
{
    return false;
}

bool Food::matable(OrganicEntity const *other) const {
    return other->canMate(this);
}

bool Food::canMate(A_Unused Scorpion const *scorpion) const {
    return false;
}

bool Food::canMate(A_Unused Gerbil const *gerbil) const {
    return false;
}

bool Food::canMate(A_Unused Food const *food) const {
    return false;
}
