#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "engine/util/CommonIncludes.h"
#include "engine/screen.h"

class Application;
class TickSystem;

class EndScreen : public Screen{
public:
    EndScreen(std::shared_ptr<Application> application);


public:
    void onSwitch() override;

    void draw(Graphics *g) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // ENDSCREEN_H
