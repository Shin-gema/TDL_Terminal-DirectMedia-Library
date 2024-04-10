/*
** EPITECH PROJECT, 2024
** opti_curse
** File description:
** resize
*/

#include "../texture.hpp"
#include "../../window/window.hpp"
#include <stdexcept>
#include <png.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../../logger/logger.hpp"
#include <cmath>
#include "../Vector.hpp"

/**
 * Resize the image to the outputWidth and outputHeight size
 *
 * @param outputWidth the new width of the image in pixel
 * @param outputHeight the new height of the image in pixel
 * @result set the _pixelsTabResized to the new resized image
 *
 * @throws std::runtime_error if the width or height is 0
 * @exceptsafe strong the function does not resize the image if the width or height is 0
 *
 * @warning the function can occur data loss if the size is to small
 * @note The algorithm used is the Nearest Neighbor it is the fastest but the less accurate
 */
void Texture::resizeImage(u_int32_t outputWidth, u_int32_t outputHeight) {
    if (outputWidth == 0 || outputHeight == 0)
        throw std::runtime_error("Width and Height must be greater than 0");
    else {
        if (!_pixelsTabResized.empty())
            _pixelsTabResized.clear();
        std::vector<std::vector<pixel_color>> newPixelsTab(outputHeight, std::vector<pixel_color>(outputWidth,pixel_color(0, 0, 0,0)));
        for (u_int32_t y = 0; y < outputHeight; y++) {
            for (u_int32_t x = 0; x < outputWidth; x++) {
                int x_ratio = (int) ((x * (_widthResized - 1)) / outputWidth);
                int y_ratio = (int) ((y * (_heightResized - 1)) / outputHeight);
                pixel_color color;
                color.color = _pixelsTabResized[y_ratio][x_ratio].color;
                newPixelsTab[y][x] = color;
            }
        }
        _pixelsTabResized = newPixelsTab;
        _widthResized = outputWidth;
        _heightResized = outputHeight;
    }
}

/**
 * Resize the image to the scaleX and scaleY size
 * @param scaleX the new width scale of the image
 * @param scaleY the new height scale of the image
 * @overload
 */
void Texture::resizeImage(double scaleX, double scaleY) {
    _swidth = scaleX;
    _sheight = scaleY;
}

/**
 * Resize the image to the scale size
 * @param scale the new width and height scale of the image
 *
 * @overload
 */
void Texture::resizeImage(double scale) {
    _swidth = scale;
    _sheight = scale;
}