/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** texture.cpp
*/

#include "texture.hpp"
#include "../window/window.hpp"
#include <stdexcept>
#include <png.h>
#include <iostream>
#include <vector>
#include <algorithm>

Texture::Texture(std::string path)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
}

Texture::Texture(std::string path, textureRect rect)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
    _rect = rect;

}

Texture::~Texture()
{
    png_destroy_read_struct(&_png_ptr, &_info_ptr, NULL);
}

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

void Texture::loadFromFile(std::string path)
{
    _path = path;
    if (!is_png(path.c_str()))
        throw std::runtime_error("File is not a png");
    loadTexture();
    loadPixels();
}

void Texture::loadTexture()
{
    FILE *fp = fopen(_path.c_str(), "rb");
    _png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info_ptr = png_create_info_struct(_png_ptr);
    png_init_io(_png_ptr, fp);
    png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    _width = png_get_image_width(_png_ptr, _info_ptr);
    _height = png_get_image_height(_png_ptr, _info_ptr);
    _channels = png_get_channels(_png_ptr, _info_ptr);
    _bit_depth = png_get_bit_depth(_png_ptr, _info_ptr);
    _row_pointers = png_get_rows(_png_ptr, _info_ptr);
    fclose(fp);
}

void Texture::resizeImage(u_int64_t outputWidth, u_int64_t outputHeight) {
    if (outputWidth == _width && outputHeight == _height)
        return;
    if (!_pixelsTabResized.empty())
        _pixelsTabResized.clear();
    std::vector<std::vector<pixel_color>> newPixelsTab;
    newPixelsTab.resize(outputHeight);
    for (u_int64_t y = 0; y < outputHeight; y++) {
        newPixelsTab[y].resize(outputWidth);
        for (u_int64_t x = 0; x < outputWidth; x++) {
            int x_ratio = (int) ((x * (_width - 1)) / outputWidth);
            int y_ratio = (int) ((y * (_height - 1)) / outputHeight);
            pixel_color color;
            color.color = _pixelsTab[y_ratio][x_ratio].color;
            newPixelsTab[y][x] = color;
        }
    }
     _pixelsTabResized = newPixelsTab;
    _widthResized = outputWidth;
    _heightResized = outputHeight;
}

void Texture::resizeImage(float scale) {
    int outputWidth = _width * scale;
    int outputHeight = _height * scale;
    resizeImage(outputWidth, outputHeight);
}


pixel_color Texture::blendColor(pixel_color bg, pixel_color fg){
    pixel_color result = {0};
    float alpha = fg.a / 255.0;
    result.r = bg.r * (1 - alpha) + fg.r * alpha;
    result.g = bg.g * (1 - alpha) + fg.g * alpha;
    result.b = bg.b * (1 - alpha) + fg.b * alpha;
    result.a = std::clamp(bg.a + fg.a, 0, 255);
    return result;
}

void Texture::loadPixels()
{
    if (_channels != 4)
        throw std::runtime_error("Texture must have 4 channels");
    if (_pixelsTab.size() > 0)
        _pixelsTab.clear();
    for (u_int64_t y = 0; y < _height; y++) {
        std::vector<pixel_color> row;
        for (u_int64_t x = 0; x < _width; x++) {
            png_byte *ptr = &(_row_pointers[y][x * _channels]);
            pixel_color color;
            color.r = ptr[0];
            color.g = ptr[1];
            color.b = ptr[2];
            color.a = ptr[3];
            row.push_back(color);
        }
        _pixelsTab.push_back(row);
    }
}

bool isBlackPixel(pixel_color color) {
    return color.a == 0;
}

void Texture::drawTextureRect(Window *win)
{
    int i = _posX;
    int j = _posY;
    for (u_int64_t y = _rect->y; y < _rect->y + _rect->height && y < _heightResized ; y++) {
        for (u_int64_t x = _rect->x; x < _rect->x + _rect->width && x <_widthResized; x++) {
            if (_tint.has_value() && !isBlackPixel(_pixelsTabResized[y][x]))
                win->setPixel(i,j, blendColor(win->getPixelColor(i, j), blendColor(_pixelsTabResized[y][x], _tint.value())));
            else
                win->setPixel(i, j, blendColor(win->getPixelColor(i, j), _pixelsTabResized[y][x]));
            i++;
        }
        j++;
        i = _posX;
    }
}

void Texture::drawTextureResized(Window *win) {
    u_int64_t i = _posX;
    u_int64_t j = _posY;
    for (u_int64_t y = 0; y < _heightResized; y++) {
        for (u_int64_t x = 0; x < _widthResized; x++) {
            if (_tint.has_value() && !isBlackPixel(_pixelsTabResized[y][x])) {
                pixel_color color = blendColor(_pixelsTabResized[y][x], _tint.value());
                win->setPixel(i, j, blendColor(win->getPixelColor(i, j), color));
            } else
                win->setPixel(i, j, blendColor(win->getPixelColor(i, j), _pixelsTabResized[y][x]));
            i++;
        }
        j++;
        i = _posX;
    }
}

void Texture::draw(Window *win) {
    if (_rect.has_value())
        drawTextureRect(win);
    else
        drawTextureResized(win);
}