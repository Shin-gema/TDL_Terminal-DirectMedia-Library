
#ifndef TDL_TRANSFORM_HPP
    #define TDL_TRANSFORM_HPP

    #include "tdl/Vector.hpp"

    #include "tdl/Matrix/PixelMatrix.hpp"
    #include "tdl/Math/UnitConverter.hpp"


#include "tdl/Rect.hpp"

namespace tdl {
    class Transform {
        public:
        constexpr Transform() :
            m_matrix{1, 0, 0, 0, 1, 0, 0, 0, 1}
        {
        }

        constexpr Transform(float a, float b, float c, float d, float e, float f, float g, float h, float i) :
            m_matrix{a, b, c, d, e, f, g, h, i}
        {
        }

        [[nodiscard]] constexpr const float *getMatrix() const
        {
            return m_matrix;
        }

        constexpr Transform &combine(const Transform &transform)
        {
            const float *b = transform.m_matrix;
            const float *a = m_matrix;
            //clang-format off
            *this = Transform( a[0] * b[0] + a[1] * b[3] + a[2] * b[6],
                               a[0] * b[1] + a[1] * b[4] + a[2] * b[7],
                               a[0] * b[2] + a[1] * b[5] + a[2] * b[8],
                               a[3] * b[0] + a[4] * b[3] + a[5] * b[6],
                               a[3] * b[1] + a[4] * b[4] + a[5] * b[7],
                               a[3] * b[2] + a[4] * b[5] + a[5] * b[8],
                               a[6] * b[0] + a[7] * b[3] + a[8] * b[6],
                               a[6] * b[1] + a[7] * b[4] + a[8] * b[7],
                               a[6] * b[2] + a[7] * b[5] + a[8] * b[8]);
            //clang-format on
            return *this;
        }

        [[nodiscard]] constexpr Vector2f transformPoint(float x, float y) const
        {
            return {m_matrix[0] * x + m_matrix[1] * y + m_matrix[2],
                            m_matrix[3] * x + m_matrix[4] * y + m_matrix[5]};
        }

        [[nodiscard]] constexpr Vector2f transformPoint(const Vector2f &point) const
        {
            return transformPoint(point.x(), point.y());
        }

        [[nodiscard]] constexpr RectF transformRect(const RectF &rectangle) const
        {
            const float left = rectangle.x();
            const float right = rectangle.y();
            const float top = rectangle.height();
            const float bottom = rectangle.width();

            const Vector2f points[] = {transformPoint(left, top),
                                       transformPoint(right, top),
                                       transformPoint(left, bottom),
                                       transformPoint(right, bottom)};

            float minX = points[0].x();
            float maxX = points[0].x();
            float minY = points[0].y();
            float maxY = points[0].y();

            for (int i = 1; i < 4; ++i)
            {
                const float x = points[i].x();
                const float y = points[i].y();

                if (x < minX)
                    minX = x;
                else if (x > maxX)
                    maxX = x;

                if (y < minY)
                    minY = y;
                else if (y > maxY)
                    maxY = y;
            }

            return {minX, minY, maxX - minX, maxY - minY};
        }

        constexpr Transform &translate(float x, float y)
        {
            // clang-format off
            const Transform transform(1.f, 0.f, x,
                                      0.f, 1.f, y,
                                      0.f, 0.f, 1.f);
            // clang-format on
            return combine(transform);
        }

        constexpr Transform &rotate(float angle)
        {
            const float rad = UnitConverter<double>::toRadians(angle);
            const float s = std::sin(rad);
            const float c = std::cos(rad);
            // clang-format off
            const Transform transform(c, -s, 0.f,
                                      s, c, 0.f,
                                      0.f, 0.f, 1.f);
            // clang-format on
            return combine(transform);
        }

        constexpr Transform &rotate(float angle, float centerX, float centerY)
        {
            translate(centerX, centerY);
            rotate(angle);
            return translate(-centerX, -centerY);
        }

        constexpr Transform &rotate(float angle, const Vector2f &center)
        {
            return rotate(angle, center.x(), center.y());
        }

        constexpr Transform &scale(float scaleX, float scaleY)
        {
            // clang-format off
            const Transform transform(scaleX, 0.f, 0.f,
                                      0.f, scaleY, 0.f,
                                      0.f, 0.f, 1.f);
            // clang-format on
            return combine(transform);
        }

        constexpr Transform &scale(const Vector2f &factors)
        {
            return scale(factors.x(), factors.y());
        }

    private:
        float m_matrix[9];
    };

    constexpr Transform operator * (const Transform &left, const Transform &right)
    {
        Transform result = left;
        return result.combine(right);
    }
    constexpr Transform &operator *= (Transform &left, const Transform &right)
    {
        return left.combine(right);
    }

    constexpr Vector2f operator * (const Transform &left, const Vector2f &right)
    {
        return left.transformPoint(right);
    }

    constexpr Vector2f operator *= (const Transform &right, const Vector2f &left)
    {
        return right.transformPoint(left);
    }

    PixelMatrix operator * (const Transform &left, PixelMatrix &right);

    constexpr bool operator == (const Transform &left, const Transform &right)
    {
        const float *a = left.getMatrix();
        const float *b = right.getMatrix();
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] &&
               a[3] == b[3] && a[4] == b[4] && a[5] == b[5] &&
               a[6] == b[6] && a[7] == b[7] && a[8] == b[8];
    }

    constexpr bool operator != (const Transform &left, const Transform &right)
    {
        return !(left == right);
    }
}
#endif //TDL_TRANSFORM_HPP
