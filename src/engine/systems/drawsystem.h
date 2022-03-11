#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

#include <QGLWidget>

class Graphics;

class DrawSystem  : public System {
public:
    DrawSystem();

    SystemFlag systemFlag() override;

    void draw(Graphics *g) override;
};

#endif // DRAWSYSTEM_H
