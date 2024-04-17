
#include "Window/window.hpp"
#include "Texture/Texture.hpp"
#include "Vector.hpp"
#include "Rect.hpp"
#include "Pixel/Pixel.hpp"
#include <optional>

#ifndef SPRITE_HPP
    #define SPRITE_HPP

namespace tdl {
    class Sprite {
        public :

            Sprite *createSprite(Texture *texture, Vector2u pos);
            Sprite *createSprite(Texture *texture, Vector2u pos, RectU rect);
            ~Sprite();

            void setTexture(Texture *texture) { _texture = texture;}
            void setRect(RectU rect) { _rect = rect;}

            Texture *getTexture() { return _texture;}
            RectU getRect() { return _rect;}

            void drawOn(Window *window);

        private : 
            Sprite(Texture *texture, Vector2u pos);
            Sprite(Texture *texture, Vector2u pos, RectU rect);
            bool isBlackPixel(Pixel pixel);

            Texture *_texture;
            Vector2u _pos;
            RectU _rect;
            std::optional<Pixel> _tint;
    };
}

#endif // SPRITE_HPP