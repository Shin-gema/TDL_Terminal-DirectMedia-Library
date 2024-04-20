
#include "../../include/Window/window.hpp"

/**
 * @brief ansii front color code
 * 
 * @param pixel the pixel to get the color
 */
void tdl::Window::setRGBFrontGround(Pixel pixel)
{
    _content += "\033[38;2;" + std::to_string(GET_R(pixel.color)) + ";" + std::to_string(GET_G(pixel.color)) + ";" + std::to_string(GET_B(pixel.color)) + "m";

}

/**
 * @brief ansii back color code
 * 
 * @param pixel the pixel to get the color
 */

void tdl::Window::setRGBBackGround(Pixel pixel)
{
    _content += "\033[48;2;" + std::to_string(GET_R(pixel.color)) + ";" + std::to_string(GET_G(pixel.color)) + ";" + std::to_string(GET_B(pixel.color)) + "m";
}

/**
 * @brief ansii clear screen code
 * 
 */
void tdl::Window::clearScreen()
{
    _content += "\033[2J";
}

/**
 * @brief ansii move cursor code
 * 
 * @param pos the position to move the cursor
 */
void tdl::Window::moveCursor(Vector2u pos)
{
    _content += "\033[" + std::to_string(y(pos) / 2) + ";" + std::to_string(x(pos)) + "H";
}

/**
 * @brief ansii print pixel code
 * 
 */
void tdl::Window::printPixel()
{
    //_content += std::string(reinterpret_cast<const char*>("A"));
    _content += std::string(reinterpret_cast<const char*>(u8"\u2584"));
}

/**
 * @brief ansii alternate screen buffer code
 * 
 */
void tdl::Window::alternateScreenBuffer()
{
    _content += "\033[?1049h";
}

/**
 * @brief ansii remove mouse cursor code
 * 
 */
void tdl::Window::removeMouseCursor()
{
    _content += "\033[?25l";
}
