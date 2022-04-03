#ifndef ELLIPSOIDCOMPONENT_H
#define ELLIPSOIDCOMPONENT_H

#include "engine/component.h"

class Graphics;
class Ellipsoid;

class EllipsoidComponent : public Component{
public:
    EllipsoidComponent(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Ellipsoid>);

    EllipsoidComponent(std::shared_ptr<GameObject> gameObject,
                       std::shared_ptr<Ellipsoid>,
                       QString texture);

    SystemFlag requiresSystems() override { return DRAW_SYSTEM;}

    void draw(Graphics *g) override;

private:
    std::shared_ptr<Ellipsoid> ellipsoid;
    QString texture = "";
};

#endif // ELLIPSOIDCOMPONENT_H
