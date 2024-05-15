
#include <string>
#include <png.h>
#include <vector>
#include "tdl/Vector.hpp"
#include <iostream>
#include "tdl/Texture/TextureLoader.hpp"

/**
 * @brief Construct a new tdl::Texture Loader::Texture Loader object
 * 
 * @param path the path to the png file to load 
 * @note on this version, the texture loader only loads png files
 */
tdl::TextureLoader::TextureLoader(std::string path) : _path(path), _info_ptr(nullptr), _row_pointers(nullptr), _png_ptr(nullptr), _size(0, 0), _channels(0), _bit_depth(0)
{
    if(path != "")
        loadTexture();
}

/**
 * @brief Destroy the tdl::Texture Loader::Texture Loader object
 * 
 */
tdl::TextureLoader::~TextureLoader()
{
    if (_info_ptr != nullptr)
        png_destroy_read_struct(&_png_ptr, &_info_ptr, nullptr);
    if (_row_pointers != nullptr)
        delete[] _row_pointers;
}

/**
 * @brief check if the file is a png file
 * 
 * @param fd the file to check
 * @return true if the file is a png file
 * @return false if the file is not a png file
 */
bool tdl::TextureLoader::isPng(std::string path)
{
    FILE* file = fopen(path.c_str(), "rb");
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    png_byte header[8];
    fread(header, 1, 8, file);
    fclose(file);

    return !png_sig_cmp(header, 0, 8);
}

/**
 * @brief load the texture from the given path
 * 
 * @param path the path to the png file to load
 * @note this function is the init of the texture loader
 */
void tdl::TextureLoader::loadTexture(std::string path)
{
    _path = path;
    FILE *fp = fopen(_path.c_str(), "rb");
    if (!fp)
        throw std::runtime_error("Failed to open file");
    if (!isPng(path))
        throw std::runtime_error("File is not a png");
    _png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info_ptr = png_create_info_struct(_png_ptr);
    png_init_io(_png_ptr, fp);
    png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_GRAY_TO_RGB, NULL);
    _size = Vector2u(png_get_image_width(_png_ptr, _info_ptr), png_get_image_height(_png_ptr, _info_ptr));
    _channels = png_get_channels(_png_ptr, _info_ptr);
    _bit_depth = png_get_bit_depth(_png_ptr, _info_ptr);
    _row_pointers = png_get_rows(_png_ptr, _info_ptr);
    
    fclose(fp);
}

/**
 * @brief load the texture from the stock path
 * @overload
 */
void tdl::TextureLoader::loadTexture()
{
    loadTexture(_path);
}