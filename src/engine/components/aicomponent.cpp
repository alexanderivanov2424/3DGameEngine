#include "aicomponent.h"

AIComponent::AIComponent(std::shared_ptr<GameObject> g)  : Component(g){

}


void AIComponent::tick(float seconds){
    btNode->tick(seconds);
}


void AIComponent::setBTNode(std::shared_ptr<BTNode> btNode){
    this->btNode = btNode;
}
