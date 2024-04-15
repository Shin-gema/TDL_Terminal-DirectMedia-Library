
#ifndef TEXTURELOADER_HPP
    #define TEXTURELOADER_HPP

#include <string>
#include <png.h>
#include <vector>
#include "Vector.hpp"

namespace tdl {
    class TextureLoader {
        protected :
            TextureLoader(std::string path);
            ~TextureLoader();
            void loadTexture();
            void loadTexture(std::string path);

        protected :
            bool isPng(FILE *fd);
            //png variables
            std::string _path;
            png_infop _info_ptr;
            png_bytepp _row_pointers;
            png_structp _png_ptr;
            Vector2u _size;
            int _channels;
            int _bit_depth;
    };
}

#endif /* !TEXTURELOADER_HPP */
