
#include "tdl/Window/window.hpp"
#include "tdl/Drawable/Texture/Texture.hpp"
#include "tdl/Vector.hpp"
#include "tdl/Rect.hpp"
#include "tdl/Pixel/Pixel.hpp"
#include "tdl/Matrix/Transformation.hpp"
#include "tdl/Drawable/Drawable.hpp"
#include <optional>

#ifndef SPRITE_HPP
    #define SPRITE_HPP

namespace tdl {
    class Sprite : public Transformable, public Drawable {
        public :

            static Sprite *createSprite(Texture *texture, Vector2u &pos);
            static Sprite *createSprite(Texture *texture, Vector2u &pos, RectU &rect);
            ~Sprite() override;

            void setTexture(Texture *texture) { _texture = texture;}
            void setTint(Pixel tint) { _tint = tint;}

            Texture *getTexture() { return _texture;}
            Pixel getTint() { return _tint.value_or(Pixel(0, 0, 0, 0));}

            //void drawOn(Window *window);
            void draw(Drawable *drawable) override;
            static Pixel lerp(Pixel a, Pixel b, double t);

        private : 
            Sprite(Texture *texture, Vector2u &pos);
            Sprite(Texture *texture, Vector2u &pos, RectU &rect);

            static bool isBlackPixel(Pixel pixel);

            Texture *_texture;
            Vector2u _pos;
            std::optional<Pixel> _tint;
    };
}

#endif // SPRITE_HPP