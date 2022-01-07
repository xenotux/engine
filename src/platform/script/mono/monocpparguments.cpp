/**
 *  Mana - 3D Game Engine
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

#ifdef BUILD_ENGINE_SCRIPT_MONO

#include "platform/script/mono/monocpparguments.hpp"

#include "platform/script/mono/monocppobject.hpp"

namespace xengine {
    void MonoCppArguments::add(int &value) {
        args.emplace_back(&value);
    }

    void MonoCppArguments::add(float &value) {
        args.emplace_back(&value);
    }

    void MonoCppArguments::add(double &value) {
        args.emplace_back(&value);
    }

    void MonoCppArguments::add(const MonoCppObject &value) {
        args.emplace_back(value.getObjectPointer());
    }

    void MonoCppArguments::clear() {
        args.clear();
    }

    const std::vector<void *> &MonoCppArguments::data() const {
        return args;
    }

    size_t MonoCppArguments::count() const {
        return args.size();
    }
}

#endif