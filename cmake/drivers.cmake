option(DRIVER_GLFW "Build the glfw display driver" ON)
option(DRIVER_OPENGL "Build the OpenGL render driver (Window and Render implementations" ON)
option(DRIVER_OPENGL_QT "Build the Qt render driver (Window and Render implementations)" ON)
option(DRIVER_MONO "Build the mono script driver" ON)
option(DRIVER_BOX2D "Build the box2d physics driver" ON)
option(DRIVER_BULLET3 "Build the bullet3 physics driver" ON)
option(DRIVER_OPENAL "Build the OpenAL audio driver" ON)
option(DRIVER_FREETYPE "Build the FreeType font rendering driver" ON)
option(DRIVER_ASSIMP "Build the AssImp resource parser driver (For 3D asset file formats)" ON)
option(DRIVER_SNDFILE "Build the SndFile resource parser driver (For Audio file formats)" ON)

set(DRIVERS_INCLUDE)
set(DRIVERS_SRC)
set(DRIVERS_LINK)

set(Drivers.GLOBEXPR)

if (DRIVER_MONO)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/mono/*.cpp drivers/mono/*.c)
    add_compile_definitions(DRIVER_MONO)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/mono/)
    set(DRIVERS_LINK ${DRIVERS_LINK} mono-2.0)
endif ()

if (DRIVER_BOX2D)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/box2d/*.cpp drivers/box2d/*.c)
    add_compile_definitions(BOX2D_VERSION=${BOX2D_VERSION})
    add_compile_definitions(DRIVER_BOX2D)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/box2d/)
    set(DRIVERS_LINK ${DRIVERS_LINK} ${BOX2D_LIB})
endif ()

if (DRIVER_BULLET3)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/bullet3/*.cpp drivers/bullet3/*.c)
    add_compile_definitions(DRIVER_BULLET3)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/bullet3/)
endif ()

if (DRIVER_OPENAL)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/openal/*.cpp drivers/openal/*.c)
    add_compile_definitions(DRIVER_OPENAL)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/openal/)
    set(DRIVERS_LINK ${DRIVERS_LINK} openal)
endif ()

if (DRIVER_GLFW)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/glfw/*.cpp drivers/glfw/*.c)
    add_compile_definitions(DRIVER_GLFW)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/glfw/)
    set(DRIVERS_LINK ${DRIVERS_LINK} glfw)
endif ()

if (DRIVER_OPENGL)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/opengl/*.cpp drivers/opengl/*.c)
    add_compile_definitions(DRIVER_OPENGL)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/opengl/)
    set(DRIVERS_LINK ${DRIVERS_LINK} GL)
endif ()

if (DRIVER_OPENGL_QT)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)

    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/opengl-qt/*.cpp drivers/opengl-qt/*.c)
    add_compile_definitions(DRIVER_OPENGL_QT)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/opengl-qt/)
    set(DRIVERS_LINK ${DRIVERS_LINK} GL Qt5::Core Qt5::Widgets)
endif ()

if (DRIVER_FREETYPE)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/freetype/*.cpp drivers/freetype/*.c)
    add_compile_definitions(DRIVER_FREETYPE)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/freetype/)
    set(DRIVERS_LINK ${DRIVERS_LINK} freetype)
endif ()

if (DRIVER_ASSIMP)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/assimp/*.cpp drivers/assimp/*.c)
    add_compile_definitions(DRIVER_ASSIMP)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/assimp/)
    set(DRIVERS_LINK ${DRIVERS_LINK} assimp)
endif ()

if (DRIVER_SNDFILE)
    set(Drivers.GLOBEXPR ${Drivers.GLOBEXPR} drivers/sndfile/*.cpp drivers/sndfile/*.c)
    add_compile_definitions(DRIVER_SNDFILE)
    set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} drivers/sndfile/)
    set(DRIVERS_LINK ${DRIVERS_LINK} sndfile)
endif ()

file(GLOB_RECURSE DRIVERS_SRC ${Drivers.GLOBEXPR})