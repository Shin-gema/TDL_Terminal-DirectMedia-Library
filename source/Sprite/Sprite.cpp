
#include "Sprite/Sprite.hpp"
#include "Vector.hpp"
#include "Rect.hpp"
#include "Pixel/Pixel.hpp"
#include "Window/window.hpp"
#include <optional>

/**
 * @brief Create a Sprite object
 * 
 * @param texture the texture of the sprite to create
 * @param pos the position of the sprite
 * @return tdl::Sprite* the sprite created
 */
tdl::Sprite *tdl::Sprite::createSprite(tdl::Texture *texture, tdl::Vector2u pos)
{
    return new tdl::Sprite(texture, pos);
}

/**
 * @brief Create a Sprite object with an pos and a rect
 * 
 * @param texture the texture of the sprite to create
 * @param pos the position of the sprite
 * @param rect the rect of the sprite
 * @return tdl::Sprite* the sprite created
 */
tdl::Sprite* tdl::Sprite::createSprite(tdl::Texture *texture, tdl::Vector2u pos, tdl::RectU rect)
{
    return new tdl::Sprite(texture, pos, rect);
}

/**
 * @brief Construct a new tdl::Sprite::Sprite object
 * 
 * @param texture the texture of the sprite
 * @param pos the position of the sprite
 */
tdl::Sprite::Sprite(tdl::Texture *texture, tdl::Vector2u pos)
{
    _texture = texture;
    _pos = pos;
    tdl::Vector2u size = texture->getSize();
    _rect = tdl::RectU(0, 0, x(size), y(size));
}

/**
 * @brief Construct a new tdl::Sprite::Sprite object
 * 
 * @param texture the texture of the sprite
 * @param pos the position of the sprite
 * @param rect the rect of the sprite
 */
tdl::Sprite::Sprite(Texture *texture, Vector2u pos, RectU rect)
{
    _texture = texture;
    _pos = pos;
    _rect = rect;
}

/**
 * @brief Destroy the tdl::Sprite::Sprite object
 * @note it will delete the texture of the sprite
 */
tdl::Sprite::~Sprite()
{
    delete _texture;
}

/**
 * @brief check if the pixel is black
 * 
 * @param pixel the pixel to check
 * @return true if the pixel is black
 * @return false if the pixel is not black
 */
bool tdl::Sprite::isBlackPixel(Pixel pixel)
{
    return static_cast<uint8_t>(GET_R(pixel.color)) == 0 && static_cast<uint8_t>(GET_G(pixel.color)) == 0 && static_cast<uint8_t>(GET_B(pixel.color)) == 0;
}

/**
 * @brief draw the sprite on the window
 * 
 * @param window the window to draw the sprite on
 */
void tdl::Sprite::drawOn(Window *window)
{
    u_int32_t i = x(_pos);
    u_int32_t j = y(_pos);
    u_int32_t width = tdl::width(_rect);
    u_int32_t height = tdl::height(_rect);
    u_int32_t size_x = tdl::x(_texture->getSize());
    u_int32_t size_y = tdl::y(_texture->getSize());

    static tdl::Vector2f saveScale = Vector2f(1.0, 1.0);
    if (_texture->getScale() != saveScale) {
        _texture->resizeImage();
        saveScale = _texture->getScale();
        size_x = tdl::x(_texture->getSize());
        size_y = tdl::y(_texture->getSize());
    }

    for (u_int32_t y = tdl::y(_rect); y < height + tdl::y(_rect) && y < size_y; y++) {
        for (u_int32_t x = tdl::x(_rect); x < width + tdl::x(_rect) && x < size_x; x++) {
            if (_tint.has_value() && !isBlackPixel(_texture->getPixel(Vector2u(x, y)))) {
                Pixel color = window->getPixel(Vector2u(i, j)) + _texture->getPixel(Vector2u(x, y)) + _tint.value();
                window->setPixel(Vector2u(i, j), color);
            } else {
                tdl::Pixel color = window->getPixel(Vector2u(i, j)) + _texture->getPixel(Vector2u(x, y));
                window->setPixel(Vector2u(i, j), color);
            }
            i++;
        }
        i = x(_pos);
        j++;
    }
}