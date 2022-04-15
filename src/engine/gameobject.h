#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "engine/util/CommonIncludes.h"
#include "engine/util/TypeMap.h"
#include <QGLWidget>

class Component;
class GameWorld;



class GameObject
{
public:
    GameObject(std::shared_ptr<GameWorld> gameWorld);

    template <typename Comp> void addComponent(std::shared_ptr<Comp> &&c){
        components.put<Comp>(std::forward<std::shared_ptr<Comp>>(c));
    }
    template <typename Comp> void removeComponent(){
        components.remove<Comp>();
    }

    template <typename Comp> std::shared_ptr<Comp> getComponent(){
        auto it = components.find<Comp>();
        return std::static_pointer_cast<Comp>(it->second);
    }

    template <typename Comp> bool hasComponent(){
        return components.find<Comp>() != components.end();
    }

    TypeMap<std::shared_ptr<Component>>::iterator begin(){
        return components.begin();
    }
    TypeMap<std::shared_ptr<Component>>::iterator end(){
        return components.end();
    }

public:
    std::shared_ptr<GameWorld> gameWorld;

private:
    TypeMap<std::shared_ptr<Component>> components;

};

#endif // GAMEOBJECT_H
