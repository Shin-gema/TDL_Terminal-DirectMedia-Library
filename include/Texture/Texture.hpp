
#ifndef TEXTURE_HPP
    #define TEXTURE_HHP

#include <string>
#include <vector>
#include "Texture/TextureLoader.hpp"
#include "Vector.hpp"
#include "Rect.hpp"
#include "Pixel/Pixel.hpp"

namespace tdl {
    class Texture : public TextureLoader {
        public : 

            ~Texture();

            static Texture *createTexture(std::string path);
            static Texture *createTexture(std::string path, Vector2f scale);
            static Texture *createTexture(std::string path, bool repeat);
            static Texture *createTexture(std::string path, Vector2f scale, bool repeat);

            static Texture *createTextureFromVector(Pixel *pixelData, Vector2u size);
            static Texture *createTextureFromVector(Pixel * pixelData, Vector2u size, Vector2f scale);
            static Texture *createTextureFromVector(Pixel * pixelData, Vector2u size, bool repeat);
            static Texture *createTextureFromVector(Pixel * pixelData, Vector2u size, Vector2f scale, bool repeat);

            void resizeImage();
            void loadPixels();

            void setScale(Vector2f scale) {_scale = scale;}
            void setRepeat(bool repeat) { _repeat = repeat;}
            void setRect(RectU rect) {_rect = rect;}

            Vector2f getScale() {return _scale;}
            bool getRepeat() {return _repeat;}
            RectU getRect() {return _rect;}
            Pixel getPixel(Vector2u pos);

        private : 
            Texture(std::string path, Vector2f scale, bool repeat);
            Texture(Pixel *pixelData, Vector2u size, Vector2f scale, bool repeat);

            std::vector<std::vector<Pixel>> _pixelData;
            Vector2f _scale;
            bool _repeat;
            RectU _rect;
    };
}
#endif // TEXTURE_HPP