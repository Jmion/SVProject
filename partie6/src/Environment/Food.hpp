//
// Created by jeremy on 4/2/19.
//

#ifndef PARTIE1_FOOD_HPP
#define PARTIE1_FOOD_HPP

#include <Environment/OrganicEntity.hpp>

class Food : public OrganicEntity
{

public:

    /*!
     * Position where the food will be spawned
     * @param position where the food will be spawned
     */
    explicit Food(const Vec2d &position);

    ~Food() override ;

    void draw(sf::RenderTarget &target) const override;

    void update(sf::Time dt) override;

private:

    /*!
     *
     * @return the size of the food given in the config file
     */
    double getSize() const;

    /*!
     * @return the path to the food texture as given in the config file
     */
    std::string getTexturePath() const;

    /*!
     * @return the initial energy level of a plant.
     */
    double getEnergy() const;

public:
    bool eatable(OrganicEntity const *entity) const override;

    bool eatableBy(Scorpion const *scorpion) const override;

    bool eatableBy(Gerbil const *gerbil) const override;

    bool eatableBy(Food const *food) const override;

    bool eatableBy(Dragon const *dragon) const override;

    bool meet(OrganicEntity *mate) override;

    bool meetManagement(Scorpion *mate) override;

    bool meetManagement(Gerbil *mate) override;

    bool meetManagement(Food *mate) override;

    bool meetManagement(Dragon *mate) override;

    bool matable(OrganicEntity const *other) const override;

    bool canMate(Scorpion const *scorpion) const override;

    bool canMate(Gerbil const *gerbil) const override;

    bool canMate(Food const *food) const override;

    bool canMate(Dragon const *dragon) const override;

};


#endif //PARTIE1_FOOD_HPP
