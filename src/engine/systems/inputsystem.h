#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "engine/util/CommonIncludes.h"
#include "engine/systems/system.h"

class InputSystem : public System {
public:
    InputSystem();

    SystemFlag systemFlag() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyRepeatEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // INPUTSYSTEM_H
