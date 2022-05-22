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

#include "cast/numeric_cast.hpp"

#include "render/platform/opengl/oglrenderallocator.hpp"

#include "render/platform/opengl/openglinclude.hpp"
#include "render/platform/opengl/oglrendertarget.hpp"
#include "render/platform/opengl/ogltexturebuffer.hpp"
#include "render/platform/opengl/oglmeshbuffer.hpp"
#include "render/platform/opengl/oglshaderprogram.hpp"

#include "render/shader/shadercompiler.hpp"

namespace xengine {
    namespace opengl {
        static std::string getGlsl(const ShaderSource &source) {
            if (source.getLanguage() == GLSL_410)
                return source.getSrc();
            else
                return ShaderCompiler::crossCompile(source.getSrc(),
                                                    source.getEntryPoint(),
                                                    source.getStage(),
                                                    source.getLanguage(),
                                                    GLSL_410);
        }

        static GLenum getElementType(Mesh::Primitive primitive) {
            switch (primitive) {
                case Mesh::POINT:
                    return GL_POINTS;
                case Mesh::LINE:
                    return GL_LINES;
                case Mesh::TRI:
                    return GL_TRIANGLES;
                default:
                    throw std::runtime_error("Unsupported primitive");
            }
        }


        std::unique_ptr<RenderTarget> OGLRenderAllocator::createRenderTarget(Vec2i size) {
            return std::make_unique<OGLRenderTarget>(size);
        }

        std::unique_ptr<RenderTarget> OGLRenderAllocator::createRenderTarget(Vec2i size, int samples) {
            return std::make_unique<OGLRenderTarget>(size, samples);
        }

        std::unique_ptr<TextureBuffer> OGLRenderAllocator::createTextureBuffer(TextureBuffer::Attributes attributes) {
            return std::make_unique<OGLTextureBuffer>(attributes);
        }

        std::unique_ptr<MeshBuffer> OGLRenderAllocator::createMeshBuffer(const Mesh &mesh) {
            auto ret = std::make_unique<OGLMeshBuffer>();

            try {
                ret->elementType = getElementType(mesh.primitive);
            } catch (std::exception &e) {
                throw e;
            }

            ret->indexed = mesh.indexed;
            ret->instanced = false;

            Mat4f offset = MatrixMath::identity(); // Default instancing offset is identity.

            if (mesh.indexed) {
                ret->elementCount = mesh.indices.size();

                glGenVertexArrays(1, &ret->VAO);
                glGenBuffers(1, &ret->VBO);
                glGenBuffers(1, &ret->EBO);
                glGenBuffers(1, &ret->instanceVBO);

                glBindVertexArray(ret->VAO);

                glBindBuffer(GL_ARRAY_BUFFER, ret->VBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Vertex) * mesh.vertices.size()),
                             mesh.vertices.data(),
                             GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret->EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(uint) * mesh.indices.size()),
                             mesh.indices.data(),
                             GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(4);
                glEnableVertexAttribArray(5);
                glEnableVertexAttribArray(6);
                glEnableVertexAttribArray(7);
                glEnableVertexAttribArray(8);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
                // normal attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
                // uv attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
                // tangent attribute
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (8 * sizeof(float)));
                // bitangent attribute
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (11 * sizeof(float)));

                glBindBuffer(GL_ARRAY_BUFFER, ret->instanceVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Mat4f), &offset, GL_STATIC_DRAW);

                // instanceMatrix attribute
                glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) 0);
                glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) Mat4f::ROW_SIZE);
                glVertexAttribPointer(7,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (2 * Mat4f::ROW_SIZE));
                glVertexAttribPointer(8,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (3 * Mat4f::ROW_SIZE));

                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);

                glBindVertexArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            } else {
                ret->elementCount = mesh.vertices.size();

                glGenVertexArrays(1, &ret->VAO);
                glGenBuffers(1, &ret->VBO);
                glGenBuffers(1, &ret->instanceVBO);

                glBindVertexArray(ret->VAO);

                glBindBuffer(GL_ARRAY_BUFFER, ret->VBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Vertex) * mesh.vertices.size()),
                             mesh.vertices.data(),
                             GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(4);
                glEnableVertexAttribArray(5);
                glEnableVertexAttribArray(6);
                glEnableVertexAttribArray(7);
                glEnableVertexAttribArray(8);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
                // normal attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
                // uv attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
                // tangent attribute
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (8 * sizeof(float)));
                // bitangent attribute
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (11 * sizeof(float)));

                glBindBuffer(GL_ARRAY_BUFFER, ret->instanceVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(Mat4f), &offset, GL_STATIC_DRAW);

                // instanceMatrix attribute
                glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) 0);
                glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) Mat4f::ROW_SIZE);
                glVertexAttribPointer(7,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (2 * Mat4f::ROW_SIZE));
                glVertexAttribPointer(8,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (3 * Mat4f::ROW_SIZE));

                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);

                glBindVertexArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            checkGLError("OGLRenderAllocator::createMeshBuffer");

            return ret;
        }

        std::unique_ptr<MeshBuffer> OGLRenderAllocator::createInstancedMeshBuffer(const Mesh &mesh,
                                                                                  const std::vector<Transform> &offsets) {
            auto ret = std::make_unique<OGLMeshBuffer>();

            try {
                ret->elementType = getElementType(mesh.primitive);
            } catch (std::exception &e) {
                throw e;
            }

            ret->indexed = mesh.indexed;

            ret->instanced = true;
            ret->instanceCount = offsets.size();

            Mat4f off[offsets.size()];

            for (int i = 0; i < offsets.size(); i++) {
                off[i] = MatrixMath::translate(offsets.at(i).getPosition())
                         * MatrixMath::scale(offsets.at(i).getScale())
                         * offsets.at(i).getRotation().matrix();
            }

            if (mesh.indexed) {
                ret->elementCount = mesh.indices.size();

                glGenVertexArrays(1, &ret->VAO);
                glGenBuffers(1, &ret->VBO);
                glGenBuffers(1, &ret->EBO);
                glGenBuffers(1, &ret->instanceVBO);

                glBindVertexArray(ret->VAO);

                glBindBuffer(GL_ARRAY_BUFFER, ret->VBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Vertex) * mesh.vertices.size()),
                             mesh.vertices.data(),
                             GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret->EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(uint) * mesh.indices.size()),
                             mesh.indices.data(),
                             GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(4);
                glEnableVertexAttribArray(5);
                glEnableVertexAttribArray(6);
                glEnableVertexAttribArray(7);
                glEnableVertexAttribArray(8);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
                // normal attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
                // uv attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
                // tangent attribute
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (8 * sizeof(float)));
                // bitangent attribute
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (11 * sizeof(float)));

                glBindBuffer(GL_ARRAY_BUFFER, ret->instanceVBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Mat4f) * offsets.size()),
                             &off[0],
                             GL_STATIC_DRAW);

                // instanceMatrix attribute
                glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) 0);
                glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) Mat4f::ROW_SIZE);
                glVertexAttribPointer(7,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (2 * Mat4f::ROW_SIZE));
                glVertexAttribPointer(8,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (3 * Mat4f::ROW_SIZE));

                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);

                glBindVertexArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            } else {
                ret->elementCount = mesh.vertices.size();

                glGenVertexArrays(1, &ret->VAO);
                glGenBuffers(1, &ret->VBO);
                glGenBuffers(1, &ret->instanceVBO);

                glBindVertexArray(ret->VAO);

                glBindBuffer(GL_ARRAY_BUFFER, ret->VBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Vertex) * mesh.vertices.size()),
                             mesh.vertices.data(),
                             GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(4);
                glEnableVertexAttribArray(5);
                glEnableVertexAttribArray(6);
                glEnableVertexAttribArray(7);
                glEnableVertexAttribArray(8);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
                // normal attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
                // uv attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
                // tangent attribute
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (8 * sizeof(float)));
                // bitangent attribute
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (11 * sizeof(float)));

                glBindBuffer(GL_ARRAY_BUFFER, ret->instanceVBO);
                glBufferData(GL_ARRAY_BUFFER,
                             numeric_cast<GLsizeiptr>(sizeof(Mat4f) * offsets.size()),
                             &off[0],
                             GL_STATIC_DRAW);

                // instanceMatrix attribute
                glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) 0);
                glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void *) Mat4f::ROW_SIZE);
                glVertexAttribPointer(7,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (2 * Mat4f::ROW_SIZE));
                glVertexAttribPointer(8,
                                      4,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      sizeof(Mat4f),
                                      (void *) (3 * Mat4f::ROW_SIZE));

                glVertexAttribDivisor(5, 1);
                glVertexAttribDivisor(6, 1);
                glVertexAttribDivisor(7, 1);
                glVertexAttribDivisor(8, 1);

                glBindVertexArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            checkGLError("OGLRenderAllocator::createMeshInstanced");

            return ret;
        }

        std::unique_ptr<MeshBuffer> OGLRenderAllocator::createCustomMeshBuffer(
                const RenderAllocator::CustomMeshDefinition &mesh) {
            throw std::runtime_error("Not Implemented");
        }

        // TODO: Implement GL_ARB_gl_spirv extension support
        std::unique_ptr<ShaderProgram> OGLRenderAllocator::createShaderProgram(const SPIRVSource &vertexShader,
                                                                               const SPIRVSource &fragmentShader) {
            std::string vs = ShaderCompiler::decompileSPIRV(vertexShader.blob,
                                                            vertexShader.entryPoint,
                                                            VERTEX,
                                                            GLSL_410);
            std::string fs = ShaderCompiler::decompileSPIRV(fragmentShader.blob,
                                                            fragmentShader.entryPoint,
                                                            FRAGMENT,
                                                            GLSL_410);
            return std::make_unique<OGLShaderProgram>(vs, fs);
        }

        std::unique_ptr<ShaderProgram> OGLRenderAllocator::createShaderProgram(const SPIRVSource &vertexShader,
                                                                               const SPIRVSource &fragmentShader,
                                                                               const SPIRVSource &geometryShader) {
            std::string vs = ShaderCompiler::decompileSPIRV(vertexShader.blob,
                                                            vertexShader.entryPoint,
                                                            VERTEX,
                                                            GLSL_410);
            std::string fs = ShaderCompiler::decompileSPIRV(fragmentShader.blob,
                                                            fragmentShader.entryPoint,
                                                            FRAGMENT,
                                                            GLSL_410);
            std::string gs = ShaderCompiler::decompileSPIRV(geometryShader.blob,
                                                            geometryShader.entryPoint,
                                                            GEOMETRY,
                                                            GLSL_410);
            return std::make_unique<OGLShaderProgram>(vs, fs, gs);
        }

        std::unique_ptr<ShaderProgram> OGLRenderAllocator::createShaderProgram(const ShaderSource &vertexShader,
                                                                               const ShaderSource &fragmentShader) {
            std::string vs = getGlsl(vertexShader);
            std::string fs = getGlsl(fragmentShader);
            return std::make_unique<OGLShaderProgram>(vs, fs);
        }

        std::unique_ptr<ShaderProgram> OGLRenderAllocator::createShaderProgram(const ShaderSource &vertexShader,
                                                                               const ShaderSource &fragmentShader,
                                                                               const ShaderSource &geometryShader) {
            std::string vs = getGlsl(vertexShader);
            std::string fs = getGlsl(fragmentShader);
            std::string gs = getGlsl(geometryShader);
            return std::make_unique<OGLShaderProgram>(vs, fs, gs);
        }

        std::unique_ptr<ShaderProgram> OGLRenderAllocator::createShaderProgram(const ShaderBinary &shader) {
            return std::make_unique<OGLShaderProgram>(shader);
        }
    }
}