//
// Created by jeremy on 5/5/19.
//

#ifndef PARTIE1_MAT2D_HPP
#define PARTIE1_MAT2D_HPP

#include <Utility/Vec2d.hpp>


/*!
 * @class Mat2d
 *
 * @brief Provides a incomplete implementation of 2d Matrix.
 *
 *
 */
class Mat2d
{
public:
    /*!
     * Builds the indentity matrix
     */
    Mat2d();

    /*!
     * Builds a matrix with the following parameters. Using standard numbering of matrix arguments.
     *
     * | 00 | 01 |
     * | 10 | 11 |
     *
     * @param _00 parameter place in location 00
     * @param _01 parameter place in location 01
     * @param _10 parameter place in location 10
     * @param _11 parameter place in location 11
     */
    Mat2d(double _00, double _01, double _10, double _11);

    /*!
     * Copy constructor
     * @param m
     */
    Mat2d(const Mat2d & m);


    /*!
     * Creates a rotation matrix on angle.
     * Angle in radians
     * @param angle
     */
    Mat2d(double radAngle);

    Vec2d operator*(Vec2d const & b) const;


private:
    double data[4];
};


#endif //PARTIE1_MAT2D_HPP
