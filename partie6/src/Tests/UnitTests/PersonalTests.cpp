//
// Created by jeremy on 5/5/19.
//
#include <Utility/Vec2d.hpp>
#include <Utility/Mat2d.hpp>
#include <iostream>

int main(){
    Vec2d v(1, 0);
    Mat2d m(PI/2);
    Vec2d res = m * v;
    std::cout<< "["<<res[0]<< " , "<<res[1]<<"]"<< std::endl;
}
