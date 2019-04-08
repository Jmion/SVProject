//
// Created by jeremy on 4/8/19.
//

#ifndef PARTIE1_MACROS_HPP
#define PARTIE1_MACROS_HPP
//Supress unused warning
#define A_Unused __attribute__((unused))

#include <boost/preprocessor.hpp>

/*############ MACRO FOR ENUM WITH TO STRING ##################################
 * This is a usefull method since it ensures that the name of the enum is the
 * same as the string that is returned when the ToString macro is called.
 *
This macro can be called as follows:

 DEFINE_ENUM_WITH_STRING_CONVERSIONS(OS_type, (Linux)(Apple)(Windows))

 followed by using it in the main as follows:

int main()
{
    OS_type t = Windows;
    std::cout << ToString(t) << " " << ToString(Apple) << std::endl;
}

Copied from https://stackoverflow.com/questions/5093460/how-to-convert-an-enum-type-variable-to-a-string
 */
#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem)    \
    case elem : return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                \
    enum name {                                                               \
        BOOST_PP_SEQ_ENUM(enumerators)                                        \
    };                                                                        \
                                                                              \
    inline const char* ToString(name v) const                                       \
    {                                                                         \
        switch (v)                                                            \
        {                                                                     \
            BOOST_PP_SEQ_FOR_EACH(                                            \
                X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE,          \
                name,                                                         \
                enumerators                                                   \
            )                                                                 \
            default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
        }                                                                     \
    }


// #############################################################################





#endif //PARTIE1_MACROS_HPP
