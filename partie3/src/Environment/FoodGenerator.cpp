//
// Created by jeremy on 4/2/19.
//

#include "FoodGenerator.hpp"
#include <Application.hpp>
#include <Environment/Food.hpp>
#include <Random/Normal.hpp>

FoodGenerator::FoodGenerator() :timeSinceLastFoodSpawn(sf::Time::Zero){

}

void FoodGenerator::update(sf::Time dt) {
    timeSinceLastFoodSpawn += dt;
    if(dt > sf::seconds(getAppConfig().food_generator_delta)){
        dt = sf::Time::Zero;
        double worldSize = getAppConfig().simulation_world_size;
        double center = worldSize/2;
        double var = (worldSize/4)*(worldSize/4);
        getAppEnv().addEntity(new Food(Vec2d(normal(center,var),normal(center,var))));
    }
}
