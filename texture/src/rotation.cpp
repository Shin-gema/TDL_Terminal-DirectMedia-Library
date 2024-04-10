/*
** EPITECH PROJECT, 2024
** opti_curse
** File description:
** rotation
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
 * Set X offset on the source matrix and set the target matrix with the new values
 * @param alpha the angle of the shear
 * @param[out] target the new matrix with the shear on it
 * @param[in] source the source matrix
 * @see [Shear Matrix](https://www.ocf.berkeley.edu/~fricke/projects/israel/paeth/rotation_by_shearing.html)
 * @note The algorithm used is the Shear it is the fastest and one of the most accurate for this use case
 * @note We can maybe implement antialiasing to improve the quality of the image
 * @warning the function can crash for now if use badly
 * @warning This function cannot be used alone, it must only be call by rotate methode
 */
void Texture::xShear(double alpha, std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    OC::Vector2u end = {height, width};
    std::vector<int> skewis(height);
    int min_skewi = 0;
    for (int y = 0; y < height; y++) {
        double skew = (alpha) * y;
        int skewi = static_cast<int>(std::floor(skew));
        skewis[y] = skewi;
        if (skewi < min_skewi) 
            min_skewi = skewi;
    }

    u_int newWidth = 0;
    if (min_skewi < 0) {
        min_skewi = -min_skewi;
        newWidth = width + min_skewi;
    } else {
        min_skewi = 0;
        int skewi = skewis[height - 1] + min_skewi;
        OC::x(end) = OC::x(end) + skewi + width;
        newWidth = std::max(OC::x(end) , width);
    }

    std::vector<std::vector<pixel_color>> data_out(height, std::vector<pixel_color>(newWidth, pixel_color(0, 0, 0, 0)));

    for (int y = 0; y < height; y++) {
        double skew = alpha * y;
        int skewi = skewis[y] + min_skewi;
        double skewf = skew - skewi;
        pixel_color oleft;

        for (int x = width - 1; x >= 0; x--) {
            pixel_color pixel = source[y][x];
            pixel_color left(pixel.r * skewf, pixel.g * skewf, pixel.b * skewf, pixel.a * skewf);

            pixel.color = (pixel.color - left.color) + oleft.color;
            if (x + skewi >= 0 && x + skewi < newWidth) 
                data_out[y][x + skewi] = pixel;
            oleft = left;
        }
        if (skewi + 1 >= 0 && skewi + 1 < newWidth )
            data_out[y][skewi + 1] = oleft;
    }

    target = data_out;
    _heightResized = target.size();
    _widthResized = target[0].size();
}

/**
 * Set Y offset on the source matrix and set the target matrix with the new values
 * @param alpha the angle of the shear
 * @param[out] target the new matrix with the shear on it
 * @param[in] source the source matrix
 * @see [Shear Matrix](https://www.ocf.berkeley.edu/~fricke/projects/israel/paeth/rotation_by_shearing.html)
 * @note The algorithm used is the Shear it is the fastest and one of the most accurate for this use case
 * @note We can maybe implement antialiasing to improve the quality of the image
 * @warning the function can crash for now if use badly
 * @warning This function cannot be used alone, it must only be call by rotate methode
 */
void Texture::yShear(double beta, std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    OC::Vector2u end = {height, width};

    std::vector<int> skewis(width);
    int min_skewi = 0;
    for (int x = 0; x < width; x++) {
        double skew = beta * x;
        int skewi = static_cast<int>(std::floor(skew));
        skewis[x] = skewi;
        if (skewi < min_skewi) 
            min_skewi = skewi;
    }

    u_int newHeight = 0;
    if (min_skewi < 0) {
        min_skewi = -min_skewi;
        newHeight = height + min_skewi;

    } else {
        min_skewi = 0;
        int skewi = skewis[width - 1] + min_skewi;
        OC::y(end) = OC::y(end) + skewi + height;
        newHeight = std::max(OC::y(end) , height);

    }

    std::vector<std::vector<pixel_color>> data_out(newHeight, std::vector<pixel_color>(width , pixel_color(0, 0, 0, 0)));

    for (int x = 0; x < width; x++) {
        double skew = beta * x;
        int skewi = skewis[x] + min_skewi;
        double skewf = skew - skewi;
        pixel_color oleft;

        for (int y = height - 1; y >= 0; y--) {
            pixel_color pixel = source[y][x];
            pixel_color left(pixel.r * skewf, pixel.g * skewf, pixel.b * skewf, pixel.a * skewf);

            pixel.color = (pixel.color - left.color) + oleft.color;
            if (y + skewi >= 0 && y + skewi < newHeight) 
                data_out[y + skewi][x] = pixel;
            oleft = left;
        }
        if (skewi + 1 >= 0 && skewi + 1 < newHeight) 
            data_out[skewi + 1][x] = oleft;
    }

    target = data_out;
    _heightResized = target.size();
    _widthResized = target[0].size();
}

/**
 * Mirror the image on the Y axis
 * @param[out] target The matrix with the Y axis mirror on it
 * @param[in] source the initial matrix
 */
void Texture::mirrorY(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    for (u_int y = 0; y < height; y++) {
        for (u_int x = 0; x < width; x++)
            target[y][x] = source[height - y - 1][x];
    }
    _heightResized = target.size();
    _widthResized = target[0].size();
}

/**
 * Mirror the image on the Y axis
 * @param[out] target The matrix with the X axis mirror on it
 * @param[in] source the initial matrix
 */
void Texture::mirrorX(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    for (u_int y = 0; y < height; y++) {
        for (u_int x = 0; x < width; x++) 
            target[y][x] = source[y][width - x - 1];
    }
    _heightResized = target.size();
    _widthResized = target[0].size();
}

/**
 * apply rotation on the image
 * @param angle the angle of the rotation in degree
 * @note The algorithm used is the Shear it is the fastest and one of the most accurate for this use case
 * @warning the function can crash for now if use badly whith crop image
 */
void Texture::rotate(float angle)
{
    double theta = (angle / 180.0) * M_PI;
    if (theta > (0.5) * M_PI && theta < (1.5) * M_PI) {
        mirrorY(_pixelsTabResized, _pixelsTabResized);
        mirrorX(_pixelsTabResized, _pixelsTabResized);
        theta = theta - M_PI;
    }
    double alpha = -tan(theta / 2);
    double beta = sin(theta);

    xShear(alpha, _pixelsTabResized, _pixelsTabResized);
    yShear(beta, _pixelsTabResized, _pixelsTabResized);
    xShear(alpha, _pixelsTabResized, _pixelsTabResized);

    int start_y = 0;
    for (u_int32_t y = 0; y < _heightResized; y++) {
        bool isBlack = true;
        for (u_int32_t x = 0; x < _widthResized; x++) {
            if ((_pixelsTabResized[y][x]) != pixel_color(0, 0, 0, 0)) {
                isBlack = false;
                break;
            }
        }
        if (!isBlack) {
            start_y = y;
            break;
        }
    }

    int start_x = 0;
    for (u_int32_t x = 0; x < _widthResized; x++) {
        bool isBlack = true;
        for (u_int32_t y = 0; y < _heightResized; y++) {
            if ((_pixelsTabResized[y][x]) != pixel_color(0, 0, 0, 0)) {
                isBlack = false;
                break;
            }
        }
        if (!isBlack) {
            start_x = x;
            break;
        }
    }

    for (std::vector<pixel_color> &pixel : _pixelsTabResized) 
        pixel.erase(pixel.begin(), pixel.begin() + start_x);

    for (int i = 0; i < start_y; i++) 
        _pixelsTabResized.erase(_pixelsTabResized.begin());

    _heightResized = _pixelsTabResized.size();
    _widthResized = _pixelsTabResized[0].size();
}