/**
 *  xEngine - C++ game engine library
 *  Copyright (C) 2021  Julian Zampiccoli
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef XENGINE_MOUSE_HPP
#define XENGINE_MOUSE_HPP

#include "math/vector2.hpp"

namespace xengine {
    enum MouseButton {
        LEFT,
        MIDDLE,
        RIGHT,
        OPTIONAL_1,
        OPTIONAL_2,
        OPTIONAL_3,
        OPTIONAL_4,
        OPTIONAL_5,
        MOUSE_BUTTON_UNDEFINED
    };

    class XENGINE_EXPORT Mouse {
    public:
        bool getButton(MouseButton button) const {
            return buttonsDown.find(button) != buttonsDown.end();
        }

        double wheelDelta;
        Vec2d position;
        std::set<MouseButton> buttonsDown;
    };
}

#endif //XENGINE_MOUSE_HPP