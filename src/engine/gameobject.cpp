#include "gameobject.h"


#include "engine/gameworld.h"

GameObject::GameObject(std::shared_ptr<GameWorld> gameWorld){
    this->gameWorld = gameWorld;
}

//template <typename Comp>
//void GameObject::addComponent(std::shared_ptr<Comp> &&c){
//    components.put<Comp>(std::forward<std::shared_ptr<Comp>>(c));
//}

//template <typename Comp>
//void GameObject::removeComponent(){
//    components.remove<Comp>();
//}

//template <typename Comp>
//std::shared_ptr<Comp> GameObject::getComponent(){
//    auto it = components.find<Comp>();
//    return std::static_pointer_cast<Comp>(it->second);
//}

//TypeMap<std::shared_ptr<Component>>::iterator GameObject::begin(){
//    return components.begin();
//}
//TypeMap<std::shared_ptr<Component>>::iterator GameObject::end(){
//    return components.end();
//}
