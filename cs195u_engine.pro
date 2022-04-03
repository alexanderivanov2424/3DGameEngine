QT += core gui opengl widgets

TARGET = cs195u_engine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += \
    libs/glew-1.10.0/src/glew.c \
    src/OBJLoader.cpp \
    src/engine/application.cpp \
    src/engine/component.cpp \
    src/engine/components/cameracomponent.cpp \
    src/engine/components/cylindercollisioncomponent.cpp \
    src/engine/components/cylindercomponent.cpp \
    src/engine/components/ellipsoidcomponent.cpp \
    src/engine/components/meshslidecomponent.cpp \
    src/engine/components/playermovementcomponent.cpp \
    src/engine/components/transformcomponent.cpp \
    src/engine/gameobject.cpp \
    src/engine/gameworld.cpp \
    src/engine/screen.cpp \
    src/engine/shapes/ellipsoid.cpp \
    src/engine/shapes/mesh.cpp \
    src/engine/systems/collisionUtils/meshcollision.cpp \
    src/engine/systems/collisionsystem.cpp \
    src/engine/systems/drawsystem.cpp \
    src/engine/systems/inputsystem.cpp \
    src/engine/systems/system.cpp \
    src/engine/systems/ticksystem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/platformer/platformerapp.cpp \
    src/platformer/platformerscreen.cpp \
    src/view.cpp \
    src/viewformat.cpp \
    src/engine/graphics/ResourceLoader.cpp \
    src/engine/graphics/FBO.cpp \
    src/engine/graphics/IBO.cpp \
    src/engine/graphics/Texture.cpp \
    src/engine/graphics/Texture1D.cpp \
    src/engine/graphics/Texture2D.cpp \
    src/engine/graphics/Texture3D.cpp \
    src/engine/graphics/VAO.cpp \
    src/engine/graphics/VBO.cpp \
    src/engine/graphics/VBOAttribMarker.cpp \
    src/engine/graphics/Font.cpp \
    src/engine/graphics/DepthBuffer.cpp \
    src/engine/graphics/RenderBuffer.cpp \
    src/engine/graphics/GraphicsDebug.cpp \
    src/engine/graphics/Shader.cpp \
    src/engine/graphics/Camera.cpp \
    src/engine/graphics/Shape.cpp \
    src/engine/graphics/Graphics.cpp \
    src/engine/graphics/Material.cpp \
    src/engine/graphics/Light.cpp \
    src/warmup/endscreen.cpp \
    src/warmup/gamescreen.cpp \
    src/warmup/menuscreen.cpp \
    src/warmup/warmupapp.cpp \


HEADERS += \
    libs/glew-1.10.0/include/GL/glew.h \
    libs/stb/stb_rect_pack.h \
    libs/stb/stb_truetype.h \
    src/OBJLoader.h \
    src/engine/application.h \
    src/engine/component.h \
    src/engine/components/cameracomponent.h \
    src/engine/components/cylindercollisioncomponent.h \
    src/engine/components/cylindercomponent.h \
    src/engine/components/ellipsoidcomponent.h \
    src/engine/components/meshslidecomponent.h \
    src/engine/components/playermovementcomponent.h \
    src/engine/components/transformcomponent.h \
    src/engine/gameobject.h \
    src/engine/gameworld.h \
    src/engine/screen.h \
    src/engine/shapes/ellipsoid.h \
    src/engine/shapes/mesh.h \
    src/engine/systems/collisionUtils/meshcollision.h \
    src/engine/systems/collisionsystem.h \
    src/engine/systems/drawsystem.h \
    src/engine/systems/inputsystem.h \
    src/engine/systems/system.h \
    src/engine/systems/ticksystem.h \
    src/engine/util/TypeMap.h \
    src/mainwindow.h \
    src/platformer/platformerapp.h \
    src/platformer/platformerscreen.h \
    src/view.h \
    src/viewformat.h \
    src/engine/util/CommonIncludes.h \
    src/engine/graphics/ResourceLoader.h \
    src/engine/graphics/CylinderData.h \
    src/engine/graphics/SphereData.h \
    src/engine/graphics/FBO.h \
    src/engine/graphics/IBO.h \
    src/engine/graphics/Texture.h \
    src/engine/graphics/Texture1D.h \
    src/engine/graphics/Texture2D.h \
    src/engine/graphics/Texture3D.h \
    src/engine/graphics/VAO.h \
    src/engine/graphics/VBO.h \
    src/engine/graphics/VBOAttribMarker.h \
    src/engine/graphics/CubeData.h \
    src/engine/graphics/Font.h \
    src/engine/graphics/DepthBuffer.h \
    src/engine/graphics/RenderBuffer.h \
    src/engine/graphics/GraphicsDebug.h \
    src/engine/graphics/Shader.h \
    src/engine/graphics/ShaderAttribLocations.h \
    src/engine/graphics/Camera.h \
    src/engine/graphics/Graphics.h \
    src/engine/graphics/Shape.h \
    src/engine/graphics/Material.h \
    src/engine/graphics/Light.h \
    src/engine/graphics/Constants.h \
    src/warmup/endscreen.h \
    src/warmup/gamescreen.h \
    src/warmup/menuscreen.h \
    src/warmup/warmupapp.h \


FORMS += src/mainwindow.ui

RESOURCES += \
    res/shaders/shaders.qrc \
    res/fonts/fonts.qrc \
    res/images/images.qrc

OTHER_FILES += \
    res/images/grass.png \

DISTFILES += \
    res/obj/large_environment.obj \
    res/obj/level_easy.obj \
    res/obj/level_easy.png \
    res/obj/level_easy_channels.png \
    res/obj/level_easy_navmesh.obj \
    res/obj/level_hard.obj \
    res/obj/level_hard.png \
    res/obj/level_hard_channels.png \
    res/obj/level_island.obj \
    res/obj/level_island.png \
    res/obj/level_island_channels.png \
    res/obj/level_island_navmesh.obj \
    res/obj/level_island_navmesh_eroded.obj \
    res/shaders/shader.vert \
    res/shaders/shader.frag \


INCLUDEPATH += src libs glm libs/glew-1.10.0/include
DEPENDPATH += src libs glm libs/glew-1.10.0/include

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON +=

QMAKE_CXXFLAGS += -g
