/**
 *  This file is part of xEngine, a C++ game engine library.
 *  Copyright (C) 2021  Julian Zampiccoli
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef XENGINE_EVENTBUS_HPP
#define XENGINE_EVENTBUS_HPP

#include <functional>
#include <set>
#include <mutex>

#include "event/event.hpp"
#include "event/eventlistener.hpp"
#include "util/listenable.hpp"

namespace xng {
    class XENGINE_EXPORT EventBus : public Listenable<EventListener> {
    public:
        void invoke(const Event &event) {
            std::lock_guard<std::mutex> guard(mutex);
            for (auto *receiver: listeners) {
                receiver->onEvent(event);
            }
        }

        UnregisterCallback addListener(EventListener &listener) override {
            std::lock_guard<std::mutex> guard(mutex);
            listeners.insert(&listener);
            return [this, &listener]() {
                removeListener(listener);
            };
        }

        void removeListener(EventListener &listener) override {
            std::lock_guard<std::mutex> guard(mutex);
            listeners.erase(&listener);
        }

    private:
        std::mutex mutex;
        std::set<EventListener *> listeners;
    };
}

#endif //XENGINE_EVENTBUS_HPP
