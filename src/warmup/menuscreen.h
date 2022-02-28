#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "engine/util/CommonIncludes.h"
#include "engine/screen.h"

class Application;
class TickSystem;


class MenuScreen : public Screen{
public:
    MenuScreen(std::shared_ptr<Application> application);

public:
    void onSwitch() override;

    void draw(Graphics *g) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;



private:
    std::shared_ptr<TickSystem> tickSystem;
};

#endif // MENUSCREEN_H
