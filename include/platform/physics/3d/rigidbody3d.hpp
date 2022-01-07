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

#ifndef MANA_RIGIDBODY3D_HPP
#define MANA_RIGIDBODY3D_HPP

#include <set>
#include <memory>

#include "collider3d.hpp"

namespace xengine {
    class MANA_EXPORT RigidBody3D {
    public:
        enum RigidBodyType {
            STATIC,
            KINEMATIC,
            DYNAMIC
        };

        virtual void setRigidBodyType(RigidBodyType type) = 0;

        virtual RigidBodyType getRigidBodyType() = 0;

        virtual void setPosition(const Vec3f &position) = 0;

        virtual Vec3f getPosition() = 0;

        virtual void setVelocity(const Vec3f &velocity) = 0;

        virtual Vec3f getVelocity() = 0;

        virtual void setRotation(const Vec3f &rotation) = 0;

        virtual Vec3f getRotation() = 0;

        virtual void setAngularVelocity(const Vec3f &angularVelocity) = 0;

        virtual Vec3f getAngularVelocity() = 0;

        virtual Collider3D *createCollider() = 0;

        virtual void destroyCollider(Collider3D *collider) = 0;

        virtual std::set<Collider3D *> getColliders() = 0;

    protected:
        virtual ~RigidBody3D() = default;
    };
}
#endif //MANA_RIGIDBODY3D_HPP
