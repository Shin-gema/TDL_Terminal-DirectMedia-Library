
#ifndef LIBNCURSE_RECT_HPP
    #define LIBNCURSE_RECT_HPP


#include <tuple>
#include <cstdint>
namespace tdl {
    template<typename T>
    using Rect = std::tuple<T, T, T, T>;
    using RectI = Rect<int32_t>;
    using RectU = Rect<u_int32_t>;
    using RectF = Rect<double>;
    template<typename T>
    inline T &x(Rect<T> &v)
    {
        return std::get<0>(v);
    }

    template<typename T>
    inline T &y(Rect<T> &v)
    {
        return std::get<1>(v);
    }

    template<typename T>
    inline T &width(Rect<T> &v)
    {
        return std::get<2>(v);
    }

    template<typename T>
    inline T &height(Rect<T> &v)
    {
        return std::get<3>(v);
    }
}
#endif //LIBNCURSE_RECT_HPP