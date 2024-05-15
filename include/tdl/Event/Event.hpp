
#pragma once

#include <iostream>
#include "tdl/Input/EInput.hpp"

namespace tdl {
    /**
     * @brief The event structure. It's used to handle the event in the window
     * @note if you want to add a new event, you have to add it in the union and in the enum EventType if you want to store data for the event you can add it in the struct
     */
    struct Event
    {
        /**
         * @brief The key event structure
         * it permited to register the key that is pressed or released
         */
        struct keyEvent {
            KeyCodes code;
        };

        /**
         * @brief The size event structure
         * it permited to register the size of the window
         */
        struct sizeEvent {
            int width;
            int height;
        };

        /**
         * @brief The mouse event structure
         * it permited to register the position of the mouse
         */
        struct mouseEvent {
            int x;
            int y;
        };

        /**
         * @brief The enum EventType
         * it permited to register the type of the event
         * 
         * @note if you want to add a new event, just keep count at the last position
         */
        enum EventType {
            KeyPressed,
            KeyReleased,
            MouseMoved,
            MousePressed,
            MouseReleased,
            MouseScrolled,
            WindowResized,

            count // This is not an event, it's just a marker keep it last
        };

        EventType type{};

        /**
         * @brief The union that contains all the event data
         * 
         */
        union {
            keyEvent key;
            sizeEvent size;
            mouseEvent mouse;
        };
    };
}