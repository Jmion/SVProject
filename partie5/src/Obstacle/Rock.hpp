//
// Created by jeremy on 5/2/19.
//

#ifndef PARTIE1_ROCK_HPP
#define PARTIE1_ROCK_HPP


#include "SolideObstacle.hpp"

class Rock : public SolideObstacle{
public:

    explicit Rock(const Vec2d& position);


    static double getInitialRadius();

    ~Rock() override;

protected:
    std::string getTexturePath() const override;

};


#endif //PARTIE1_ROCK_HPP
