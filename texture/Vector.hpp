/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** Vector.hpp
*/

#ifndef LIBNCURSE_VECTOR_HPP
    #define LIBNCURSE_VECTOR_HPP

#include <tuple>
#include <cstdint>

namespace OC
{
    template<typename T>
    using Vector2 = std::tuple<T, T>;
    using Vector2i = Vector2<int32_t>;
    using Vector2u = Vector2<u_int32_t>;
    using Vector2f = Vector2<double>;

    template<typename T>
    inline T &x(Vector2<T> &v)
    {
        return std::get<0>(v);
    }

    template<typename T>
    inline T &y(Vector2<T> &v)
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
