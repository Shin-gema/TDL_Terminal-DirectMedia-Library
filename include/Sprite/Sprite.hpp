
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

            static Sprite *createSprite(Texture *texture, Vector2u pos);
            static Sprite *createSprite(Texture *texture, Vector2u pos, RectU rect);
            ~Sprite();

            void setTexture(Texture *texture) { _texture = texture;}
            void setRect(RectU rect) { _rect = rect;}
            void setTint(Pixel tint) { _tint = tint;}
            void setRotation(double rotation) { _rotation = rotation;}

            Texture *getTexture() { return _texture;}
            RectU getRect() { return _rect;}
            Pixel getTint() { return _tint.value_or(Pixel(0, 0, 0, 0));}
            double getRotation() { return _rotation;}

            void drawOn(Window *window);
            Pixel lerp(Pixel a, Pixel b, double t);

        private : 
            Sprite(Texture *texture, Vector2u pos);
            Sprite(Texture *texture, Vector2u pos, RectU rect);

            bool isBlackPixel(Pixel pixel);

            Texture *_texture;
            Vector2u _pos;
            RectU _rect;
            std::optional<Pixel> _tint;
            double _rotation = 0;
    };
}

#endif // SPRITE_HPP