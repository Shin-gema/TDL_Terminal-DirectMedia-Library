
#ifndef TDL_UNITCONVERTER_HPP
    #define TDL_UNITCONVERTER_HPP

#include <numbers>

namespace tdl
{
    template<typename T>
    class UnitConverter
    {
    public:
        UnitConverter() = delete;

        constexpr static T toRadians(T degrees)
        {
            return degrees * std::numbers::pi / 180.0;
        }

        constexpr static T toDegrees(T radians)
        {
            return radians * 180.0 / std::numbers::pi;
        }
    };
}

#endif //TDL_UNITCONVERTER_HPP
