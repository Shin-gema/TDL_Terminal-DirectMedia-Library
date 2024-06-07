
#ifndef TEXTURE_HPP
    #define TEXTURE_HPP

#include <string>
#include <vector>
#include "TextureLoader.hpp"
#include "tdl/Vector.hpp"
#include "tdl/Rect.hpp"
#include "tdl/Pixel/Pixel.hpp"
#include "tdl/Matrix/Transformation.hpp"
#include "tdl/Drawable/Drawable.hpp"
#include <optional>

namespace tdl {
class Texture : public TextureLoader, public Transformable {
        public : 

            ~Texture() override;

            static Texture *createTexture(std::string path);
            static Texture *createTexture(std::string &path, bool repeat);

            static Texture *createTextureFromVector(Pixel *pixelData, Vector2u &size);
            static Texture *createTextureFromVector(Pixel *pixelData, Vector2u &size, Vector2f &scale);
            static Texture *createTextureFromVector(Pixel *pixelData, Vector2u &size, bool repeat);
            static Texture *createTextureFromVector(Pixel *pixelData, Vector2u &size, Vector2f &scale, bool repeat);

            Pixel getOriginalPixel(Vector2u &pos);
            PixelMatrix &getOriginalImageData() { return _originalImageData; }

             void setRect(const RectU& rect) { _rect = rect; }
             void setRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { _rect = RectU(x, y, width, height); }
             std::optional<RectU> &getRect() { return _rect; }
             void resetRect() { _rect = std::nullopt; }
        private :
            Texture(std::string &path, bool repeat);
            Texture(Pixel *pixelData, Vector2u &size, Vector2f &scale, bool repeat);
            void loadPixels();
            PixelMatrix _originalImageData;
            std::optional<RectU> _rect;

    };
}
#endif // TEXTURE_HPP