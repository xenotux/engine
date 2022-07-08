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

#ifndef XENGINE_WORLDBOX2D_HPP
#define XENGINE_WORLDBOX2D_HPP

#include "box2d.hpp"

#include "physics/world.hpp"

#include "physics/box2d/rigidbodybox2d.hpp"
#include "physics/box2d/jointbox2d.hpp"

namespace xng {
    class WorldBox2D : public World {
    public:
        b2World world;

        WorldBox2D();

        ~WorldBox2D() override;

        std::unique_ptr<Collider> createCollider(const ColliderShape &shape) override;

        std::unique_ptr<RigidBody> createRigidBody() override;

        std::unique_ptr<Joint> createJoint() override;

        void addContactListener(ContactListener &listener) override;

        void removeContactListener(ContactListener &listener) override;

        void setGravity(const Vec3f &gravity) override;

        void step(float deltaTime) override;
    };
}

#endif //XENGINE_WORLDBOX2D_HPP
