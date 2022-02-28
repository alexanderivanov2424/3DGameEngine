#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "engine/util/CommonIncludes.h"
#include "engine/util/TypeMap.h"
#include <QGLWidget>

class Component;

class GameObject
{
public:
    GameObject();

    template <typename Comp> void addComponent(std::shared_ptr<Comp> &&c);
    template <typename Comp> void removeComponent();

    template <typename Comp> std::shared_ptr<Comp> getComponent();

    TypeMap<std::shared_ptr<Component>>::iterator begin();
    TypeMap<std::shared_ptr<Component>>::iterator end();


private:
    TypeMap<std::shared_ptr<Component>> components;

};

#endif // GAMEOBJECT_H
