
#ifndef TDL_UNITCONVERTER_HPP
    #define TDL_UNITCONVERTER_HPP

#include <numbers>

namespace tdl
{
    /**
     * @class UnitConverter
     * @brief Class to convert units
     * 
     * @tparam T the type of the unit
     */
    template<typename T>
    class UnitConverter
    {
    public:

    /**
     * @brief Construct a new Unit Converter object
     * delete
     */
        UnitConverter() = delete;

    /**
     * @brief transform degrees to radians
     * 
     * @param degrees the degrees to transform
     * @return constexpr T the radians
     */
        constexpr static T toRadians(T degrees)
        {
            return degrees * std::numbers::pi / 180.0;
        }

    /**
     * @brief transform radians to degrees
     * 
     * @param radians the radians to transform
     * @return constexpr T the degrees
     */
        constexpr static T toDegrees(T radians)
        {
            return radians * 180.0 / std::numbers::pi;
        }
    };
}

#endif //TDL_UNITCONVERTER_HPP
