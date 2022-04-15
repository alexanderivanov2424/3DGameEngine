#include "btnode.h"

BTCompositeNode::BTCompositeNode(){
    children = std::make_shared<QList<std::shared_ptr<BTNode>>>();
}

void BTCompositeNode::reset(){
    lastRunning = 0;
    for(int i = 0; i < children->length(); i++){
        children->at(i)->reset();
    }
}

void BTCompositeNode::linkChild(std::shared_ptr<BTNode> child){
    children->append(child);
}

void BTCompositeNode::removeChild(std::shared_ptr<BTNode> child){
    children->removeOne(child);
}

std::shared_ptr<QList<std::shared_ptr<BTNode>>> BTCompositeNode::getChildren(){
    return children;
}

BTConditionNode::BTConditionNode(){

}


BTSelectorNode::BTSelectorNode(){

}

Status BTSelectorNode::tick(float seconds){
    Status status= FAIL;
    int currentChild = 0;
    while(status == FAIL && currentChild < this->children->length()){
        status = this->children->at(currentChild)->tick(seconds);
        currentChild ++;
    }
    while(currentChild < this->children->length()){
        this->children->at(currentChild)->reset();
    }
    return status;
}

BTSequenceNode::BTSequenceNode(){

}

Status BTSequenceNode::tick(float seconds){
    Status status= SUCCESS;
    for(int i = lastRunning; i < this->children->length(); i++){
        status = this->children->at(i)->tick(seconds);
        if(status != SUCCESS){
            lastRunning = i;
            return status;
        }
    }
    return status;
}
