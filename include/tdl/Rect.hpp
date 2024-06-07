
#ifndef LIBNCURSE_RECT_HPP
    #define LIBNCURSE_RECT_HPP


#include <tuple>
#include <cstdint>
namespace tdl {
    template<typename T>
    struct Rect {
        std::tuple<T, T, T, T> _values;

        constexpr Rect() : _values(0, 0, 0, 0) {}
        constexpr Rect(T x, T y, T width, T height)  : _values(x, y, width, height) {}
        constexpr Rect(const Rect &v) : _values(v.x(), v.y(), v.width(), v.height()) {}
        constexpr Rect(Rect &&v)  noexcept : _values(v.x(), v.y(), v.width(), v.height()) {}

        constexpr Rect &operator=(const Rect &v)
        {
            this->x() = v.x();
            this->y() = v.y();
            this->width() = v.width();
            this->height() = v.height();
            return *this;
        }

        constexpr Rect &operator=(Rect &&v) noexcept
        {
            this->x() = v.x();
            this->y() = v.y();
            this->width() = v.width();
            this->height() = v.height();
            return *this;
        }

        Rect operator+(const Rect &v) const
        {
            return {this->x() + v.x(), this->y() + v.y(), this->width() + v.width(), this->height() + v.height()};
        }

        Rect operator-(const Rect &v) const
        {
            return {this->x() - v.x(), this->y() - v.y(), this->width() - v.width(), this->height() - v.height()};
        }

        Rect operator*(const Rect &v) const
        {
            return {this->x() * v.x(), this->y() * v.y(), this->width() * v.width(), this->height() * v.height()};
        }

        Rect operator/(const Rect &v) const
        {
            return {this->x() / v.x(), this->y() / v.y(), this->width() / v.width(), this->height() / v.height()};
        }

        Rect operator +=(const Rect &v)
        {
            return this + v;
        }

        Rect operator -=(const Rect &v)
        {
            return this - v;
        }

        Rect operator *=(const Rect &v)
        {
            return this * v;
        }

        Rect operator /=(const Rect &v)
        {
            return this / v;
        }

        bool operator==(const Rect &v) const
        {
            return this->x() == v.x() && this->y() == v.y() && this->width() == v.width() && this->height() == v.height();
        }

        bool operator!=(const Rect &v) const
        {
            return !(*this == v);
        }

        constexpr T &x() { return std::get<0>(_values); }
        constexpr T &y() { return std::get<1>(_values); }
        constexpr T &width() { return std::get<2>(_values); }
        constexpr T &height() { return std::get<3>(_values); }

        constexpr T x() const { return std::get<0>(_values); }
        constexpr T y() const { return std::get<1>(_values); }
        constexpr T width() const { return std::get<2>(_values); }
        constexpr T height() const { return std::get<3>(_values); }
    };

    using RectI = Rect<int32_t>;
    using RectU = Rect<u_int32_t>;
    using RectF = Rect<double>;
}
#endif //LIBNCURSE_RECT_HPP