
#pragma once

    #include "tdl/Pixel/Pixel.hpp"
    #include "tdl/Vector.hpp"
    #include <vector>
    #include <iostream>


namespace tdl {
/**
 * @brief PixelMatrix class
 * this class is a matrix of pixel
 * and its implement the basic function to manipulate the matrix
 */
    class PixelMatrix {
        public:
/**
 * @brief Construct a new Pixel Matrix:: Pixel Matrix object
 * default class constructor it will be create an new matrix with 0 of size
 */
            PixelMatrix();

/**
* @brief Construct a new Pixel Matrix:: Pixel Matrix object
* it will be create an size lenght matrix with black pixel
*
* @param size the size of the matrix
*/
            PixelMatrix(Vector2u size);

/**
 * @brief Destroy the Pixel Matrix:: Pixel Matrix object
 *
 */
            ~PixelMatrix();

/**
 * @brief set the pixel at the position pos with the color color
 *
 * @param pos the position of the pixel
 * @param color the color of the pixel
 */
            void setPixel(Vector2u pos, Pixel color);

/**
 * @brief get the pixel at the position pos
 * @param pos the position of the pixel
 * @return Pixel the pixel at the position pos
 */
            Pixel &getPixel(Vector2u pos) { return _pixelsTab[y(pos) * x(_size) + x(pos)]; }

/**
* @brief get an array of 3*2 pixel at the position pos
* it permited to compute pixel into char
*
* @param pos the position of the pixel
* @return Vector<Pixel> an 3*2 vector of pixel at the position pos
*/
            std::vector<Pixel> getPixelChar(Vector2u pos);

/**
 * @brief get the size of the matrix
 * @return Vector2u the size of the matrix
 */
            Vector2u getSize() const { return _size;}
            std::vector<Pixel> &getPixelsTab() { return _pixelsTab; }

/**
* @brief resize the matrix to the size size
*
* @param size the new size of the matrix
*/
            void resize(Vector2u size);

/**
 * @brief clear the matrix with black pixel
 *
 */
            void clear();

        private:
            Vector2u _size; /*!< the size of the matrix */
            std::vector<Pixel> _pixelsTab; /*!< the matrix of pixel */
    };
}