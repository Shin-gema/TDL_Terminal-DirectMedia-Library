/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** texture.hpp
*/

#ifndef LIBNCURSE_TEXTURE_HPP
    #define LIBNCURSE_TEXTURE_HPP

#include <string>
#include <png.h>
#include <vector>
#include "../window/window.hpp"
#include <optional>
#include "Vector.hpp"

struct textureRect {
    u_int32_t x;
    u_int32_t y;
    u_int32_t width;
    u_int32_t height;
};

class Texture {
    public:
        // constructor
        Texture(std::string path);
        Texture(std::string path, textureRect rect);

        //desctructor
        ~Texture();

        // Draw
        void draw(Window *win);

        // Load
        void loadFromFile(std::string path);

        // Resize Algorithms
        void resizeImage(double scaleX, double scaleY);
        void resizeImage(double scale);

        // rotate Algorithms
        void rotate(float angle);
        void crop(textureRect rect);

        // mirror Algorithms
        void mirrorY(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source);
        void mirrorX(std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source);

        // Setters
        void setPath(std::string path) { _path = path; }
        void setPos(u_int32_t x, u_int32_t y) { _posX = x; _posY = y; }
        void setTextureRect(textureRect rect) { _rect = rect; }
        void setTint(pixel_color color) { _tint = color; }
        void setDoNotRescale(bool doNotRescale) { _doNotRescale = doNotRescale; }

        //reset
        void resetTintColor() { _tint.reset(); }

        // Getters
        [[nodiscard]] std::string getPath() const { return _path; }
        [[nodiscard]] std::optional<textureRect> getRect() const { return _rect; }
        [[nodiscard]] u_int32_t getWidth() const { return _width; }
        [[nodiscard]] u_int32_t getHeight() const { return _height; }
        [[nodiscard]] std::vector<std::vector<pixel_color>> getPixelsTab() const { return _pixelsTab; }
        [[nodiscard]] int getPosX() const { return _posX; }
        [[nodiscard]] int getPosY() const { return _posY; }
        [[nodiscard]] std::optional<u_int32_t> getWidthResized() const { return _widthResized; }
        [[nodiscard]] std::optional<u_int32_t> getHeightResized() const { return _heightResized; }
        [[nodiscard]] std::vector<std::vector<pixel_color>> getPixelsTabResized() const { return _pixelsTabResized; }
        [[nodiscard]] std::optional<pixel_color> getTint() const { return _tint; }
        [[nodiscard]] bool getDoNotRescale() const { return _doNotRescale; }

    private:
        void loadTexture();
        void loadPixels();
        bool is_png(const char* file_path);
        pixel_color blendColor(pixel_color bg, pixel_color fg);
        void xShear(double beta, std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source);
        void yShear(double beta, std::vector<std::vector<pixel_color>> &target, std::vector<std::vector<pixel_color>> &source);
        void resizeImage(u_int32_t outputWidth, u_int32_t outputHeight);



        //png variables
        std::string _path;
        png_infop _info_ptr;
        png_bytepp _row_pointers;
        png_structp _png_ptr;
        u_int32_t _width;
        u_int32_t _height;
        int _channels;
        int _bit_depth;

        //texture position and rect variables
        u_int32_t _posX = 0;
        u_int32_t _posY = 0;
        std::optional<textureRect> _rect;

        // texture scaling variables
        double _swidth = 1.0;
        double _sheight = 1.0;

        // texture size variables
        u_int32_t _widthResized = _width;
        u_int32_t _heightResized = _height;

        //pixels matrix
        std::vector<std::vector<pixel_color>> _pixelsTab;
        std::vector<std::vector<pixel_color>> _pixelsTabResized = _pixelsTab;

        //tint color
        std::optional<pixel_color> _tint;

        //do rescaling
        bool _doNotRescale = false;

};
#endif //LIBNCURSE_TEXTURE_HPP
