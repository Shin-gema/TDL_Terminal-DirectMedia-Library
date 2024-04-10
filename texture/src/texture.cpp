/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** texture.cpp
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
 * Texture class contructor for constructor with path
 * @param path the path of the texture to load
 */
Texture::Texture(std::string path)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
}

/**
 * Texture class contructor for constructor with path and a rect for crop
 * @param path the path of the texture to load
 * @param rect the rect of the texture to load
 */
Texture::Texture(std::string path, textureRect rect)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
    _rect = rect;

}

/**
 * Texture class destructor
 */
Texture::~Texture()
{
    png_destroy_read_struct(&_png_ptr, &_info_ptr, NULL);
}

/**
 * check if the file is a png using the magic number.
 * @param file_path the path of the file to check
 * @return true if the file is a png, false otherwise
 * @throws std::runtime_error if the file cannot be open
 * @execptsage none the rest of the code will not work if the file cannot be open
 * @note the library used is libpng
 */
bool Texture::is_png(const char *file_path)
{
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    png_byte header[8];
    fread(header, 1, 8, file);
    fclose(file);

    return !png_sig_cmp(header, 0, 8);
}

/**
 * Load the texture from the path
 * @throws std::runtime_error if the file is not a png
 * @exceptsafe none the rest of the code will not work if the file is not a png
 * @note the library used is libpng
 */
void Texture::loadFromFile(std::string path)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
}

/**
 * Load the png information from the file it permited tç retrieve the width, height, channels and bit depth of the image
 * we also apply a transformation to the image to have at least 3 channels
 * @see [libpng documentation](http://www.libpng.org/pub/png/libpng-1.2.5-manual.html)
 * @warning this function is directly call by loadFromFile and the constructor do not call it directly
 */
void Texture::loadTexture()
{
    FILE *fp = fopen(_path.c_str(), "rb");
    _png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info_ptr = png_create_info_struct(_png_ptr);
    png_init_io(_png_ptr, fp);
    png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_GRAY_TO_RGB, NULL);
    _width = png_get_image_width(_png_ptr, _info_ptr);
    _height = png_get_image_height(_png_ptr, _info_ptr);
    _channels = png_get_channels(_png_ptr, _info_ptr);
    _bit_depth = png_get_bit_depth(_png_ptr, _info_ptr);
    _row_pointers = png_get_rows(_png_ptr, _info_ptr);
    fclose(fp);
}

/**
 * Load the pixels from the png file
 * @see [libpng documentation](http://www.libpng.org/pub/png/libpng-1.2.5-manual.html)
 * @warning this function is directly call by loadFromFile and the constructor do not call it directly
 */
void Texture::loadPixels()
{
    if (_pixelsTab.size() > 0)
        _pixelsTab.clear();
    for (u_int32_t y = 0; y < _height; y++) {
        std::vector<pixel_color> row;
        for (u_int32_t x = 0; x < _width; x++) {
            png_byte *ptr = &(_row_pointers[y][x * _channels]);
            pixel_color color;
            if (_channels == 3 || _channels == 4) {
                color.r = ptr[0];
                color.g = ptr[1];
                color.b = ptr[2];
                color.a = (_channels == 4) ? ptr[3] : 255;
            } else if (_channels == 2) {
                color.r = color.g = color.b = ptr[0];
                color.a = ptr[1];
            } else if (_channels == 1) {
                color.r = color.g = color.b = ptr[0];
                color.a = 255;
            }
            row.push_back(color);
        }
        _pixelsTab.push_back(row);
    }
    _pixelsTabResized = _pixelsTab;
    _widthResized = _width;
    _heightResized = _height;
}

/**
 * Blend two color in one
 * @param bg The color backgroud, its the base color of the blend
 * @param fg The color foreground, its the color to blend with the background
 * @return the color blend
 * @note the alpha is the opacity of the foreground color
 */
pixel_color Texture::blendColor(pixel_color bg, pixel_color fg){
    pixel_color result;
    float alpha = fg.a / 255.0;
    result.r = bg.r * (1 - alpha) + fg.r * alpha;
    result.g = bg.g * (1 - alpha) + fg.g * alpha;
    result.b = bg.b * (1 - alpha) + fg.b * alpha;
    result.a = std::clamp(bg.a + fg.a, 0, 255);
    return result;
}

/**
 * check if the color of the pixel is black
 * @param color the color of the pixel to check
 * @return true if the pixel is black, false otherwise
 */
bool isBlackPixel(pixel_color color) {
    return color.a == 0;
}

/**
 * crop the image to the rect passed in parameter
 * @param rect the rect to crop the image
 * @throws std::runtime_error if the crop out of height and width bounds
 * @exceptsafe strong the function does not crop the image if the rect is out of bounds
 */
void Texture::crop(textureRect rect)
{
    if (rect.x + rect.width > _width || rect.y + rect.height > _height)
        throw std::runtime_error("Invalid crop");
    std::vector<std::vector<pixel_color>> newPixelsTab;
    newPixelsTab.resize(rect.height);
    for (u_int32_t y = rect.y; y < rect.y + rect.height; y++) {
        newPixelsTab[y - rect.y].resize(rect.width);
        for (u_int32_t x = rect.x; x < rect.x + rect.width; x++) {
            newPixelsTab[y - rect.y][x - rect.x] = _pixelsTab[y][x];
        }
    }
    _pixelsTabResized = newPixelsTab;
    _widthResized = rect.width;
    _heightResized = rect.height;

}

/**
 * This function is in charge of drawing the texture on the window.
 * It will be in charge of crop, resize and tint the image if needed.
 * @param win the window where the texture will be drawn
 * @note the texture function like this, you set the variable correspond to rect, rotation, rescale, tint and position and call the draw function
 * The Draw function will make the render of the texture on the window with the good parameter set
 */
void Texture::draw(Window *win) {
    u_int32_t i = _posX;
    u_int32_t j = _posY;
    if (_rect.has_value())
        crop(_rect.value());
    u_int32_t width = _widthResized * _swidth;
    u_int32_t height = _heightResized * _sheight;
    if (!_doNotRescale)
        resizeImage(width + 1, height + 1);
    for (u_int32_t y = 0; y < _heightResized; y++) {
        for (u_int32_t x = 0; x < _widthResized; x++) {
            if (_tint.has_value() && !isBlackPixel(_pixelsTabResized[y][x])) {
                pixel_color color = blendColor(_pixelsTabResized[y][x], _tint.value());
                win->setPixel(i, j, blendColor(win->getPixelColor(i, j), color));
            } else {
                pixel_color color = blendColor(win->getPixelColor(i, j), _pixelsTabResized[y][x]);
                win->setPixel(i, j, color);
            }
            i++;
        }
        j++;
        i = _posX;
    }
}
