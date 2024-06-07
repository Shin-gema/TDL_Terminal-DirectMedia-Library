
#ifndef TDL_TEXT_HPP
    #define TDL_TEXT_HPP

#include "tdl/Text/Font/Font.hpp"
#include "tdl/Drawable/Drawable.hpp"
#include "tdl/Matrix/Transform.hpp"
#include "tdl/Matrix/Transformation.hpp"

namespace tdl {
    class Text : public Transformable {
    public:
        Text();
        Text(Font &font, std::string text);
        ~Text();

        void setFont(Font &font);
        Font &getFont();

        void setText(std::string text);
        std::string getText();

        void setColor(Pixel color) { _color = color; }
        std::optional<Pixel> getColor() { return _color; }
        void resetColor() { _color = std::nullopt; }

        void draw(Drawable *drawable);
    private:
        Font _font;
        std::string _text;
        std::string _oldText;
        std::optional<Pixel> _color;
    };
}

#endif //TDL_TEXT_HPP
