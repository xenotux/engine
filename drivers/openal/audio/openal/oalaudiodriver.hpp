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

#ifndef XENGINE_OALAUDIODRIVER_HPP
#define XENGINE_OALAUDIODRIVER_HPP

#include "driver/driver.hpp"

#include "audio/audiodriver.hpp"

namespace xengine {
    class OALAudioDriver : public AudioDriver {
    public:
        std::vector<std::string> getDeviceNames() override;

        std::unique_ptr<AudioDevice> createDevice() override;

        std::unique_ptr<AudioDevice> createDevice(const std::string &deviceName) override;

        std::type_index getType() override;

    };
}

#endif //XENGINE_OALAUDIODRIVER_HPP