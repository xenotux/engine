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

#ifndef XENGINE_RENDERPLATFORM_HPP
#define XENGINE_RENDERPLATFORM_HPP

namespace xengine {
    enum RenderPlatform {
        OPENGL_4_1, // OpenGL 4.1
        OPENGL_4_1_QT, // OpenGL 4.1 Render implementation which can be used with QOpenGLWidget
        DIRECTX_11,
        VULKAN
    };
}

#endif //XENGINE_RENDERPLATFORM_HPP