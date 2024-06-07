
#ifndef TDL_DRAWABLE_HPP
    #define TDL_DRAWABLE_HPP

#include "tdl/Matrix/PixelMatrix.hpp"
#include "tdl/Pixel/Pixel.hpp"
#include "tdl/Rect.hpp"

namespace tdl {
    class Drawable {
        public:
            Drawable() : _matrix(Vector2u(0, 0)), _OldMatrix(Vector2u(0, 0)) { }
            Drawable(Vector2u &size) : _matrix(size), _OldMatrix(size) { }
            Drawable(Vector2u &size, RectU &rect) : _matrix(size), _OldMatrix(size), _rect(rect) { }
            Drawable(PixelMatrix &matrix) : _matrix(matrix), _OldMatrix(matrix) { }
            Drawable(PixelMatrix &matrix, RectU &rect) : _matrix(matrix), _OldMatrix(matrix), _rect(rect) { }

            virtual void draw(Drawable *drawable) = 0;

            PixelMatrix &getMatrix() { return _matrix; }
            PixelMatrix &getOldMatrix() { return _OldMatrix; }

            void setMatrix(PixelMatrix &matrix) { _matrix = matrix; }
            void setOldMatrix(PixelMatrix &matrix) { _OldMatrix = matrix; }

            Pixel &getPixel(Vector2u pos) { return _matrix.getPixel(pos); }
            void setPixel(Vector2u pos, Pixel color) { _matrix.setPixel(pos, color); }

            Pixel &getOldPixel(Vector2u pos) { return _OldMatrix.getPixel(pos); }
            void setOldPixel(Vector2u pos, Pixel color) { _OldMatrix.setPixel(pos, color); }

            RectU &getRect() { return _rect; }
            void setRect(RectU rect) { _rect = rect; }

            void setUpdate(bool update) { this->update = update; }
            bool getUpdate() { return update; }

    protected:
        PixelMatrix _matrix;
        PixelMatrix _OldMatrix;
        RectU _rect;
        bool update = true;

    };
}

#endif //TDL_DRAWABLE_HPP
