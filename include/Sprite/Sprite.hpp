
#include "Texture/Texture.hpp"
#include "Vector.hpp"
#include "Rect.hpp"
#include "Pixel/Pixel.hpp"

#ifndef SPRITE_HPP
    #define SPRITE_HPP

namespace tdl {
    class Sprite {
        public :
            Sprite(Texture *texture, RectU rect);
            ~Sprite();

            void setTexture(Texture *texture) { _texture = texture;}
            void setRect(RectU rect) { _rect = rect;}

            Texture *getTexture() { return _texture;}
            RectU getRect() { return _rect;}

        private : 
            Texture *_texture;
            Vector2u _pos;
            RectU _rect;
    }
}

#endif // SPRITE_HPP