//
// Created by jeremy on 5/5/19.
//

#include <type_traits>
#include "Mat2d.hpp"
#include <cmath>

Mat2d::Mat2d(): Mat2d(1,0,0,1){}

Mat2d::Mat2d(double _00, double _01, double _10, double _11): data() {
    data[0] = _00;
    data[1] = _01;
    data[2] = _10;
    data[3] = _11;
}

Vec2d Mat2d::operator*(Vec2d const &b) const {
    return Vec2d(data[0]*b[0]+data[1]*b[1],data[2]*b[0]+data[3]*b[1]);
}

Mat2d::Mat2d(double radAngle): Mat2d(cos(radAngle),-sin(radAngle),
                                     sin(radAngle), cos(radAngle)) {
}

Mat2d::Mat2d(const Mat2d &m) : Mat2d(m.data[0],m.data[1],m.data[2],m.data[3]){

}


