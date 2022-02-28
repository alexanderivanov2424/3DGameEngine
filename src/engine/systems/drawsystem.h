#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

#include <QGLWidget>

class Graphics;

class DrawSystem  : public System {
public:
    DrawSystem();

    SystemFlag systemFlag();

    void draw(Graphics *g);
};

#endif // DRAWSYSTEM_H
