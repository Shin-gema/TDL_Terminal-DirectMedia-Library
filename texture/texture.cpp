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
#include "../logger/logger.hpp"
#include <cmath>
#include "Vector.hpp"

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
    png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_GRAY_TO_RGB, NULL);
    _width = png_get_image_width(_png_ptr, _info_ptr);
    _height = png_get_image_height(_png_ptr, _info_ptr);
    _channels = png_get_channels(_png_ptr, _info_ptr);
    _bit_depth = png_get_bit_depth(_png_ptr, _info_ptr);
    _row_pointers = png_get_rows(_png_ptr, _info_ptr);
    fclose(fp);
}

void Texture::resizeImage(u_int32_t outputWidth, u_int32_t outputHeight) {
    if (!_pixelsTabResized.empty())
        _pixelsTabResized.clear();
    std::vector<std::vector<pixel_color>> newPixelsTab(outputHeight, std::vector<pixel_color>(outputWidth, pixel_color(0, 0, 0, 0)));
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

void Texture::resizeImage(double scaleX, double scaleY) {
    _swidth = scaleX;
    _sheight = scaleY;
}

void Texture::resizeImage(float scale) {
    u_int32_t outputWidth = _widthResized * scale;
    u_int32_t outputHeight = _heightResized * scale;
    //resizeImage(outputWidth, outputHeight);
}

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
        if (skewi < min_skewi) {
            min_skewi = skewi;
        }
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
            if (x + skewi >= 0 && x + skewi < newWidth) {
                data_out[y][x + skewi] = pixel;
            }
            oleft = left;
        }
        if (skewi + 1 >= 0 && skewi + 1 < newWidth ) {
            data_out[y][skewi + 1] = oleft;
        }
    }

    target = data_out;
    _heightResized = target.size();
    _widthResized = target[0].size();
}

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
        if (skewi < min_skewi) {
            min_skewi = skewi;
        }
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
            if (y + skewi >= 0 && y + skewi < newHeight) {
                data_out[y + skewi][x] = pixel;
            }
            oleft = left;
        }
        if (skewi + 1 >= 0 && skewi + 1 < newHeight) {
            data_out[skewi + 1][x] = oleft;
        }
    }

    target = data_out;
    _heightResized = target.size();
    _widthResized = target[0].size();
}

void Texture::mirrorY(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    for (u_int y = 0; y < height; y++) {
        for (u_int x = 0; x < width; x++) {
            target[y][x] = source[height - y - 1][x];
        }
    }
    _heightResized = target.size();
    _widthResized = target[0].size();
}

void Texture::mirrorX(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source)
{
    u_int width = _widthResized;
    u_int height = _heightResized;

    for (u_int y = 0; y < height; y++) {
        for (u_int x = 0; x < width; x++) {
            target[y][x] = source[y][width - x - 1];
        }
    }
    _heightResized = target.size();
    _widthResized = target[0].size();
}

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

    std::vector<std::vector<pixel_color>> shearedPixelsTab = _pixelsTabResized;
    int start_y = 0;

    xShear(alpha, _pixelsTabResized, _pixelsTabResized);
    yShear(beta, _pixelsTabResized, _pixelsTabResized);
    xShear(alpha, _pixelsTabResized, _pixelsTabResized);

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

    for (std::vector<pixel_color> &pixel : _pixelsTabResized) {
        pixel.erase(pixel.begin(), pixel.begin() + start_x);
    }

    for (int i = 0; i < start_y; i++) {
        _pixelsTabResized.erase(_pixelsTabResized.begin());
    }

    _heightResized = _pixelsTabResized.size();
    _widthResized = _pixelsTabResized[0].size();
}

pixel_color Texture::blendColor(pixel_color bg, pixel_color fg){
    pixel_color result;
    float alpha = fg.a / 255.0;
    result.r = bg.r * (1 - alpha) + fg.r * alpha;
    result.g = bg.g * (1 - alpha) + fg.g * alpha;
    result.b = bg.b * (1 - alpha) + fg.b * alpha;
    result.a = std::clamp(bg.a + fg.a, 0, 255);
    return result;
}

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

bool isBlackPixel(pixel_color color) {
    return color.a == 0;
}

void Texture::drawTextureRect(Window *win)
{
    u_int32_t i = _posX;
    u_int32_t j = _posY;
    for (u_int32_t y = _rect->y; y < _rect->y + _rect->height && y < _heightResized ; y++) {
        for (u_int32_t x = _rect->x; x < _rect->x + _rect->width && x <_widthResized; x++) {
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

void Texture::drawTextureResized(Window *win) {
    u_int32_t i = _posX;
    u_int32_t j = _posY;
    if (_rect.has_value())
        crop(_rect.value());
    u_int32_t width = _widthResized * _swidth;
    u_int32_t height = _heightResized * _sheight;
    if (!_doNotRescale)
        resizeImage(width + 1, height + 1);
    for (u_int32_t y = 0; y < _heightResized; y++) {
        for (u_int32_t x = 1; x < _widthResized; x++) {
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

void Texture::draw(Window *win) {
        drawTextureResized(win);
}