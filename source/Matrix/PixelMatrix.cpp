
#include "Matrix/PixelMatrix.hpp"
#include <algorithm>
#include <iterator>
#include <vector>


namespace tdl {

    /**
     * @brief Construct a new Pixel Matrix:: Pixel Matrix object
     * default class constructor it will be create an new matrix with 0 of size
     */
    PixelMatrix::PixelMatrix() : _size(Vector2u(0, 0)) {
    }

    /**
     * @brief Construct a new Pixel Matrix:: Pixel Matrix object
     * it will be create an size lenght matrix with black pixel
     * 
     * @param size the size of the matrix
     */
    PixelMatrix::PixelMatrix(Vector2u size) : _size(size) {
        _pixelsTab = std::vector<Pixel>(x(_size) * y(_size), Pixel(0, 0, 0, 255));
    }

    /**
     * @brief Destroy the Pixel Matrix:: Pixel Matrix object
     * 
     */
    PixelMatrix::~PixelMatrix() {}

    /**
     * @brief set the pixel at the position pos with the color color
     * 
     * @param pos the position of the pixel
     * @param color the color of the pixel
     */
    void PixelMatrix::setPixel(Vector2u pos, Pixel color) {
        if (x(pos) < x(_size) && y(pos) < y(_size))
            _pixelsTab[y(pos) * x(_size) + x(pos)] = color;
    }

    /**
     * @brief get an array of 3*2 pixel at the position pos
     * it permited to compute pixel into char
     * 
     * @param pos the position of the pixel
     * @return Vector<Pixel> an 3*2 vector of pixel at the position pos
     */
    std::vector<Pixel> PixelMatrix::getPixelChar(Vector2u pos) {
        std::vector<Pixel> pixels = std::vector<Pixel>(6, Pixel(0, 0, 0, 255));
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++) {
                if (x(pos) + j < x(_size) && y(pos) + i < y(_size)) {
                    pixels[i * 2 + j] = _pixelsTab[(y(pos) + i) * x(_size) + x(pos) + j];
                }
            }
        return pixels;
    }

    /**
     * @brief resize the matrix to the size size
     * 
     * @param size the new size of the matrix
     */
    void PixelMatrix::resize(Vector2u size) {
        _size = size;
        _pixelsTab.resize(x(_size) * y(_size), Pixel(0, 0, 0, 255));
    }

    /**
     * @brief clear the matrix with black pixel
     *
     */
    void PixelMatrix::clear() {
        std::fill(_pixelsTab.begin(), _pixelsTab.end(), Pixel(0, 0, 0, 255));
    }

}