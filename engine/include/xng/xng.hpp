/**
 *  This file is part of xEngine, a C++ game engine library.
 *  Copyright (C) 2023  Julian Zampiccoli
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

#ifndef XENGINE_ENGINE_HPP
#define XENGINE_ENGINE_HPP

#include "xng/script/script.hpp"
#include "xng/script/scriptruntime.hpp"
#include "xng/script/scriptdriver.hpp"
#include "xng/geometry/vertexstream.hpp"
#include "xng/geometry/vertexbuilder.hpp"
#include "xng/geometry/primitive.hpp"
#include "xng/geometry/vertex.hpp"
#include "xng/ecs/componentregistry.hpp"
#include "xng/ecs/component.hpp"
#include "xng/ecs/entityname.hpp"
#include "xng/ecs/entityhandle.hpp"
#include "xng/ecs/systemruntime.hpp"
#include "xng/ecs/components.hpp"
#include "xng/ecs/systempipeline.hpp"
#include "xng/ecs/entity.hpp"
#include "xng/ecs/systemregistry.hpp"
#include "xng/ecs/system.hpp"
#include "xng/ecs/componentpool.hpp"
#include "xng/ecs/entityscene.hpp"
#include "xng/ecs/systems/meshrendersystem.hpp"
#include "xng/ecs/systems/spriteanimationsystem.hpp"
#include "xng/ecs/systems/audiosystem.hpp"
#include "xng/ecs/systems/canvasrendersystem.hpp"
#include "xng/ecs/systems/physicssystem.hpp"
#include "xng/ecs/systems/guieventsystem.hpp"
#include "xng/ecs/systems/eventsystem.hpp"
#include "xng/ecs/components/meshrendercomponent.hpp"
#include "xng/ecs/components/skyboxcomponent.hpp"
#include "xng/ecs/components/cameracomponent.hpp"
#include "xng/ecs/components/rigidbodycomponent.hpp"
#include "xng/ecs/components/genericcomponent.hpp"
#include "xng/ecs/components/buttoncomponent.hpp"
#include "xng/ecs/components/particlecomponent.hpp"
#include "xng/ecs/components/textcomponent.hpp"
#include "xng/ecs/components/spritecomponent.hpp"
#include "xng/ecs/components/audiosourcecomponent.hpp"
#include "xng/ecs/components/canvascomponent.hpp"
#include "xng/ecs/components/audiolistenercomponent.hpp"
#include "xng/ecs/components/canvastransformcomponent.hpp"
#include "xng/ecs/components/spriteanimationcomponent.hpp"
#include "xng/ecs/components/transformcomponent.hpp"
#include "xng/ecs/components/lightcomponent.hpp"
#include "xng/ecs/profiling/ecsprofiler.hpp"
#include "xng/ecs/profiling/ecssample.hpp"
#include "xng/ecs/profiling/ecsframelist.hpp"
#include "xng/ecs/profiling/ecsframe.hpp"
#include "xng/display/monitor.hpp"
#include "xng/display/displaydriver.hpp"
#include "xng/display/windowlistener.hpp"
#include "xng/display/windowattributes.hpp"
#include "xng/display/videomode.hpp"
#include "xng/display/window.hpp"
#include "xng/gui/textalignment.hpp"
#include "xng/gui/textrenderer.hpp"
#include "xng/gui/textlayout.hpp"
#include "xng/gui/text.hpp"
#include "xng/physics/collider.hpp"
#include "xng/physics/world.hpp"
#include "xng/physics/collidershape.hpp"
#include "xng/physics/joint.hpp"
#include "xng/physics/colliderdesc.hpp"
#include "xng/physics/physicsdriver.hpp"
#include "xng/physics/rigidbody.hpp"
#include "xng/math/vector2.hpp"
#include "xng/math/quaternion.hpp"
#include "xng/math/vector3.hpp"
#include "xng/math/rotation.hpp"
#include "xng/math/normalize.hpp"
#include "xng/math/grid.hpp"
#include "xng/math/matrixmath.hpp"
#include "xng/math/transform.hpp"
#include "xng/math/matrix.hpp"
#include "xng/math/rectangle.hpp"
#include "xng/math/vector4.hpp"
#include "xng/audio/audiosource.hpp"
#include "xng/audio/audiobuffer.hpp"
#include "xng/audio/audioformat.hpp"
#include "xng/audio/audiolistener.hpp"
#include "xng/audio/audiodriver.hpp"
#include "xng/audio/audiocontext.hpp"
#include "xng/audio/audiodevice.hpp"
#include "xng/driver/driver.hpp"
#include "xng/gpu/renderdeviceinfo.hpp"
#include "xng/gpu/gpumemory.hpp"
#include "xng/gpu/rendertarget.hpp"
#include "xng/gpu/renderbuffer.hpp"
#include "xng/gpu/vertexbufferdesc.hpp"
#include "xng/gpu/gpudriver.hpp"
#include "xng/gpu/rendertargetdesc.hpp"
#include "xng/gpu/texturearraybufferdesc.hpp"
#include "xng/gpu/vertexattribute.hpp"
#include "xng/gpu/gpumemorydesc.hpp"
#include "xng/gpu/renderproperties.hpp"
#include "xng/gpu/vertexbuffer.hpp"
#include "xng/gpu/renderbuffertype.hpp"
#include "xng/gpu/indexbuffer.hpp"
#include "xng/gpu/shaderbufferdesc.hpp"
#include "xng/gpu/renderdevicecapability.hpp"
#include "xng/gpu/indexbufferdesc.hpp"
#include "xng/gpu/texturebuffer.hpp"
#include "xng/gpu/texturearraybuffer.hpp"
#include "xng/gpu/vertexarrayobjectdesc.hpp"
#include "xng/gpu/textureproperties.hpp"
#include "xng/gpu/shaderbuffer.hpp"
#include "xng/gpu/gpufence.hpp"
#include "xng/gpu/renderobject.hpp"
#include "xng/gpu/renderpipelinedesc.hpp"
#include "xng/gpu/vertexarrayobject.hpp"
#include "xng/gpu/texturebufferdesc.hpp"
#include "xng/gpu/renderpipeline.hpp"
#include "xng/gpu/renderdevice.hpp"
#include "xng/gpu/compute/computepipelinedesc.hpp"
#include "xng/gpu/compute/computepipeline.hpp"
#include "xng/gpu/compute/computecommand.hpp"
#include "xng/gpu/raytrace/raytracepipeline.hpp"
#include "xng/gpu/raytrace/raytracecommand.hpp"
#include "xng/gpu/raytrace/raytracepipelinedesc.hpp"
#include "xng/util/numeric_cast.hpp"
#include "xng/util/refcounter.hpp"
#include "xng/util/hashcombine.hpp"
#include "xng/util/listenable.hpp"
#include "xng/util/framelimiter.hpp"
#include "xng/util/crc.hpp"
#include "xng/util/counter.hpp"
#include "xng/io/messageable.hpp"
#include "xng/io/pak.hpp"
#include "xng/io/substreambuf.hpp"
#include "xng/io/message.hpp"
#include "xng/io/readfile.hpp"
#include "xng/io/archive.hpp"
#include "xng/io/pakbuilder.hpp"
#include "xng/io/library.hpp"
#include "xng/io/protocol.hpp"
#include "xng/io/byte.hpp"
#include "xng/io/protocol/jsonprotocol.hpp"
#include "xng/io/archive/pakarchive.hpp"
#include "xng/io/archive/directoryarchive.hpp"
#include "xng/io/archive/memoryarchive.hpp"
#include "xng/resource/resourceimporter.hpp"
#include "xng/resource/resourcebundle.hpp"
#include "xng/resource/resourceregistry.hpp"
#include "xng/resource/resourceparser.hpp"
#include "xng/resource/resourceexporter.hpp"
#include "xng/resource/rawresource.hpp"
#include "xng/resource/resourcehandle.hpp"
#include "xng/resource/uri.hpp"
#include "xng/resource/resource.hpp"
#include "xng/resource/parsers/jsonparser.hpp"
#include "xng/resource/parsers/sceneparser.hpp"
#include "xng/resource/parsers/stbiparser.hpp"
#include "xng/crypto/aes.hpp"
#include "xng/crypto/gzip.hpp"
#include "xng/crypto/sha.hpp"
#include "xng/crypto/random.hpp"
#include "xng/crypto/cryptodriver.hpp"
#include "xng/app/application.hpp"
#include "xng/types/genericmap.hpp"
#include "xng/types/deltatime.hpp"
#include "xng/input/inputlistener.hpp"
#include "xng/input/input.hpp"
#include "xng/input/device/keyboard.hpp"
#include "xng/input/device/mouse.hpp"
#include "xng/input/device/gamepad.hpp"
#include "xng/input/buttonstate.hpp"
#include "xng/animation/skeletal/rig.hpp"
#include "xng/animation/skeletal/riganimator.hpp"
#include "xng/animation/skeletal/bone.hpp"
#include "xng/animation/skeletal/riganimation.hpp"
#include "xng/animation/skeletal/boneanimation.hpp"
#include "xng/animation/sprite/spritekeyframe.hpp"
#include "xng/animation/sprite/spriteanimation.hpp"
#include "xng/render/textureatlashandle.hpp"
#include "xng/render/shaderinclude.hpp"
#include "xng/render/scenerenderer.hpp"
#include "xng/render/textureatlas.hpp"
#include "xng/render/textureatlasresolution.hpp"
#include "xng/render/scene.hpp"
#include "xng/render/2d/renderer2d.hpp"
#include "xng/render/forward/forwardrenderer.hpp"
#include "xng/render/forward/forwardrenderproperties.hpp"
#include "xng/render/graph/framegraphbuilder.hpp"
#include "xng/render/graph/framegraphpassresources.hpp"
#include "xng/render/graph/framegraphrenderer.hpp"
#include "xng/render/graph/framegraphproperties.hpp"
#include "xng/render/graph/framegraphresource.hpp"
#include "xng/render/graph/framegraphpass.hpp"
#include "xng/render/graph/framegraph.hpp"
#include "xng/render/graph/framegraphallocation.hpp"
#include "xng/render/graph/framegraphallocator.hpp"
#include "xng/render/graph/passes/skyboxpass.hpp"
#include "xng/render/graph/passes/usershadepass.hpp"
#include "xng/render/graph/passes/phongforwardpass.hpp"
#include "xng/render/graph/passes/compositepass.hpp"
#include "xng/render/graph/passes/shadowmappingpass.hpp"
#include "xng/render/graph/passes/phongdeferredpass.hpp"
#include "xng/render/graph/passes/gbufferpass.hpp"
#include "xng/render/graph/passes/phongresolvepass.hpp"
#include "xng/render/graph/allocators/framegraphpoolallocator.hpp"
#include "xng/asset/skybox.hpp"
#include "xng/asset/audio.hpp"
#include "xng/asset/light.hpp"
#include "xng/asset/mesh.hpp"
#include "xng/asset/image.hpp"
#include "xng/asset/sprite.hpp"
#include "xng/asset/camera.hpp"
#include "xng/asset/color.hpp"
#include "xng/asset/shadersource.hpp"
#include "xng/asset/shader.hpp"
#include "xng/asset/texture.hpp"
#include "xng/asset/material.hpp"
#include "xng/event/eventbus.hpp"
#include "xng/event/event.hpp"
#include "xng/event/eventlistener.hpp"
#include "xng/event/events/inputevent.hpp"
#include "xng/event/events/contactevent.hpp"
#include "xng/event/events/entityevent.hpp"
#include "xng/event/events/windowevent.hpp"
#include "xng/event/events/guievent.hpp"
#include "xng/font/font.hpp"
#include "xng/font/fontdriver.hpp"
#include "xng/font/character.hpp"
#include "xng/async/threadpool.hpp"
#include "xng/async/task.hpp"
#include "xng/shader/shadercompiler.hpp"
#include "xng/shader/spirvbundle.hpp"
#include "xng/shader/spirvshader.hpp"
#include "xng/shader/shaderlanguage.hpp"
#include "xng/shader/shaderstage.hpp"
#include "xng/shader/shaderdecompiler.hpp"
#include "xng/shader/spirvblob.hpp"
#include "xng/log/loglevel.hpp"
#include "xng/log/log.hpp"

#endif // XENGINE_ENGINE_HPP