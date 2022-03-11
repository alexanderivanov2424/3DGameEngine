#ifndef CYLINDERCOMPONENT_H
#define CYLINDERCOMPONENT_H

#include "engine/component.h"

class Graphics;

class CylinderComponent : public Component{
public:
    CylinderComponent(std::shared_ptr<GameObject> gameObject,
                      float radius,
                      float height);

    CylinderComponent(std::shared_ptr<GameObject> gameObject,
                      float radius,
                      float height,
                      QString texture);

    SystemFlag requiresSystems() override { return DRAW_SYSTEM;}

    void draw(Graphics *g) override;

private:
    float radius;
    float height;
    QString texture = "";
};

#endif // CYLINDERCOMPONENT_H
