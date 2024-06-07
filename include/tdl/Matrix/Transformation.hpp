
#ifndef TDL_TRANSFORMATION_HPP
    #define TDL_TRANSFORMATION_HPP

    #include "tdl/Vector.hpp"
    #include "tdl/Matrix/Transform.hpp"

    namespace tdl
    {
        class Transformable
        {
        public:
            Transformable();
            virtual ~Transformable();

            void setPosition(const Vector2f &position);
            void setPosition(float x, float y);

            void setRotation(float angle);
            void setScale(const Vector2f &factors);
            void setScale(float factorX, float factorY);
            void setOrigin(const Vector2f &origin);
            void setOrigin(float x, float y);

            const Vector2f &getPosition() const;
            float getRotation() const;
            const Vector2f &getScale() const;
            const Vector2f &getOrigin() const;

            void move(const Vector2f &offset);
            void move(float offsetX, float offsetY);
            void rotate(float angle);
            void scale(const Vector2f &factor);
            void scale(float factorX, float factorY);

            const Transform &getTransform() const;

        protected:
            Vector2f m_origin;
            Vector2f m_position;
            Vector2f m_scale;
            float m_rotation;
            mutable Transform m_transform;
            mutable bool TransformNeedUpdate;
        };
    }

#endif //TDL_TRANSFORMATION_HPP
