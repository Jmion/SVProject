//
// Created by jeremy on 5/2/19.
//

#include "SolideObstacle.hpp"
#include <Random/Uniform.hpp>
#include <Utility/Utility.hpp>
#include <Application.hpp>

SolideObstacle::SolideObstacle(const Vec2d &postion, const double radius, const double rotation):
    CircularCollider(postion,radius), rotation(rotation)
{

}

void SolideObstacle::draw(sf::RenderTarget &target) const
{
    CircularCollider::draw(target);
    sf::Texture &texture = getAppTexture(getTexturePath());
    auto image_to_draw(buildSprite(getPosition(), getRadius() * 2, texture, getRotation() / DEG_TO_RAD));
    target.draw(image_to_draw);
}

double SolideObstacle::getRotation() const
{
    return rotation;
}


