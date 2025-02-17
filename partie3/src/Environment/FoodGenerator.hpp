//
// Created by jeremy on 4/2/19.
//

#ifndef PARTIE1_FOODGENERATOR_HPP
#define PARTIE1_FOODGENERATOR_HPP

#include <Utility/Utility.hpp>
#include <Interface/Updatable.hpp>

class FoodGenerator : public Updatable
{
public:
    void update(sf::Time dt) override;
    explicit FoodGenerator();

private:
    sf::Time timeSinceLastFoodSpawn;


};


#endif //PARTIE1_FOODGENERATOR_HPP
