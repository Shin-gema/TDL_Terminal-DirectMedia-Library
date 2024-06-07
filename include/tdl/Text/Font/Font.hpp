

#ifndef TDL_FONT_HPP
    #define TDL_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
namespace tdl {
    class Font {
    public:
        Font();

        ~Font();

        void loadFromFile(const std::string &filename);

        void setSize(unsigned int size);

        FT_Face getFace();

    private:
        FT_Library _library;
        FT_Face _face;
        unsigned int _size;
    };
}

#endif //TDL_FONT_HPP
