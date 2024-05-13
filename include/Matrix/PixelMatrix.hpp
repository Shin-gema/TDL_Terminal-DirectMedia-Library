
#pragma once

    #include "Pixel/Pixel.hpp"
    #include "Vector.hpp"
    #include <vector>
    #include <iostream>


namespace tdl {
    class PixelMatrix {
        public:
            PixelMatrix();
            PixelMatrix(Vector2u size);
            ~PixelMatrix();

            void setPixel(Vector2u pos, Pixel color);
            Pixel &getPixel(Vector2u pos) { return _pixelsTab[y(pos) * x(_size) + x(pos)]; }
            std::vector<Pixel> getPixelChar(Vector2u pos);
            Vector2u getSize() const { return _size;}
            std::vector<Pixel> &getPixelsTab() { return _pixelsTab; }
            void resize(Vector2u size);
            void clear();
            PixelMatrix operator-(const PixelMatrix &matrix);

        private:
            Vector2u _size;
            std::vector<Pixel> _pixelsTab;
    };
}