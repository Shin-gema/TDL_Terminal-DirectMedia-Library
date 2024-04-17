
/*
 * Vector.hpp
 *
 *  Created on: 26 sept. 2021
*/

#ifndef LIBNCURSE_VECTOR_HPP
    #define LIBNCURSE_VECTOR_HPP

#include <tuple>
#include <cstdint>

namespace tdl
{
    /**
     * @brief Vector template for 2D vector
     * The vector was composed like this (x, y)
     * @tparam T the type of the vector
     */
    template<typename T>
    using Vector2 = std::tuple<T, T>;
    /**
     * @brief Vector2i is a 2D vector with int32_t type
     * The vector was composed like this (x, y)
     */
    using Vector2i = Vector2<int32_t>;
    /**
     * @brief Vector2u is a 2D vector with u_int32_t type
     * The vector was composed like this (x, y)
     */
    using Vector2u = Vector2<u_int32_t>;
    /**
     * @brief Vector2f is a 2D vector with double type
     * The vector was composed like this (x, y)
     */
    using Vector2f = Vector2<double>;

    /**
     * @brief getter for x value of the vetor
     * 
     * @tparam T the type of the vector
     * @param v the vector
     * @return T& the x value of the vector
     */
    template<typename T>
    inline T x(Vector2<T> v)
    {
        return std::get<0>(v);
    }

    /**
     * @brief getter for y value of the vetor
     * 
     * @tparam T the type of the vector
     * @param v the vector
     * @return T& the y value of the vector
     */
    template<typename T>
    inline T y(Vector2<T> v)
    {
        return std::get<1>(v);
    }
    
    template<typename T>
    inline Vector2<T> operator+(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return {std::get<0>(lhs) + std::get<0>(rhs), std::get<1>(lhs) + std::get<1>(rhs)};
    }

    template<typename T>
    inline Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return {std::get<0>(lhs) - std::get<0>(rhs), std::get<1>(lhs) - std::get<1>(rhs)};
    }

    template<typename T>
    inline Vector2<T> operator*(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return {std::get<0>(lhs) * std::get<0>(rhs), std::get<1>(lhs) * std::get<1>(rhs)};
    }

    template<typename T>
    inline Vector2<T> operator/(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return {std::get<0>(lhs) / std::get<0>(rhs), std::get<1>(lhs) / std::get<1>(rhs)};
    }
}

#endif //LIBNCURSE_VECTOR_HPP
