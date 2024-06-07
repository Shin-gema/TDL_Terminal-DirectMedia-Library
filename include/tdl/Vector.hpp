
/*
 * Vector.hpp
 *
 *  Created on: 26 sept. 2021
*/

#ifndef LIBNCURSE_VECTOR_HPP
    #define LIBNCURSE_VECTOR_HPP

#include <tuple>
#include <cstdint>

#include <variant>

#include <cmath>


namespace tdl
{

/**
 * @brief Vector template for 2D vector
 * The vector was composed like this (x, y)
 * @tparam T the type of the vector
 */

    template<typename T>
    struct Vector2
    {
        std::tuple<T, T> _values;

        constexpr Vector2() : _values(0, 0) {}
        constexpr Vector2(T x, T y)  : _values(x, y) {}
        constexpr Vector2(const Vector2 &v) : _values(v.x(), v.y()) {}
        constexpr Vector2(Vector2 &&v)  noexcept : _values(v.x(), v.y()) {}

        Vector2 &operator=(const Vector2 &v)
        {
            this->x() = v.x();
            this->y() = v.y();
            return *this;
        }

        Vector2 &operator=(Vector2 &&v) noexcept
        {
            this->x() = v.x();
            this->y() = v.y();
            return *this;
        }

        Vector2 operator+(const Vector2 &v) const
        {
            return {this->x() + v.x(), this->y() + v.y()};
        }

        Vector2 operator-(const Vector2 &v) const
        {
            return {this->x() - v.x(), this->y() - v.y()};
        }

        Vector2 operator*(const Vector2 &v) const
        {
            return {this->x() * v.x(), this->y() * v.y()};
        }

        Vector2 operator/(const Vector2 &v) const
        {
            return {this->x / v.x(), this->y / v.y()};
        }

        Vector2 &operator+=(const Vector2 &v)
        {
            return *this = *this + v;
        }

        Vector2 &operator-=(const Vector2 &v)
        {
            return *this = *this - v;
        }

        Vector2 &operator*=(const Vector2 &v)
        {
            return *this = *this * v;
        }

        Vector2 &operator/=(const Vector2 &v)
        {
            return *this = *this / v;
        }

        bool operator==(const Vector2 &v) const
        {
            return this->x() == v.x() && this->y() == v.y();
        }

        bool operator!=(const Vector2 &v) const
        {
            return this->x() != v.x() || this->y() != v.y();
        }

        T dot(const Vector2 &v) const
        {
            return this->x() * v.x() + this->y() * v.y();
        }

        T cross(const Vector2 &v) const
        {
            return this->x() * v.y() - this->y() * v.x();
        }

        bool operator <=(const Vector2 &v) const
        {
            return this->x() <= v.x() && this->y() <= v.y();
        }

        bool operator >=(const Vector2 &v) const
        {
            return this->x() >= v.x() && this->y() >= v.y();
        }

    public:

/**
 * @brief getter for x value of the vetor
 *
 * @tparam T the type of the vector
 * @param v the vector
 * @return T& the x value of the vector
 */
        constexpr T& x() { return std::get<0>(_values); }

/**
 * @brief getter for y value of the vetor
 *
 * @tparam T the type of the vector
 * @param v the vector
 * @return T& the y value of the vector
 */
        constexpr T& y() { return std::get<1>(_values); }

        constexpr T y() const { return std::get<1>(_values); }
        constexpr T x() const { return std::get<0>(_values); }
    };

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
}

#endif //LIBNCURSE_VECTOR_HPP
