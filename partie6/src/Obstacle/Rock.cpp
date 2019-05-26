//
// Created by jeremy on 5/2/19.
//

#include <Application.hpp>
#include "Rock.hpp"
#include <Random/Uniform.hpp>
#include <cmath>


Rock::Rock(const Vec2d &position) :
    SolideObstacle(position, getInitialRadius(), uniform(-PI, PI))
{

}

double Rock::getInitialRadius()
{
    double minRockSize = getAppConfig().simulation_world_size / 50;
    double radius = uniform(minRockSize, 2 * minRockSize);
    return fmax(1, radius);
}

Rock::~Rock() = default;

std::string Rock::getTexturePath() const
{
    return getAppConfig().solid_obstacle_rock_texture;
}


