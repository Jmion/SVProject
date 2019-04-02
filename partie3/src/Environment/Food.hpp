//
// Created by jeremy on 4/2/19.
//

#ifndef PARTIE1_FOOD_HPP
#define PARTIE1_FOOD_HPP

#include <Environment/OrganicEntity.hpp>

class Food : public OrganicEntity{

public:

    /*!
     * Position where the food will be spawned
     * @param position where the food will be spawned
     */
    Food(const Vec2d& position);

    void draw(sf::RenderTarget &target) const override;

    void update(sf::Time dt) override;

private:

    double getSize() const;

    double getEnergy() const;

    std::string getTexturePath() const;
};


#endif //PARTIE1_FOOD_HPP
