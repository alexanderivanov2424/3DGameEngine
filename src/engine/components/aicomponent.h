#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "engine/component.h"

#include "engine/AILib/btnode.h"

class AIComponent : public Component{
public:
    AIComponent(std::shared_ptr<GameObject> gameObject);

    SystemFlag requiresSystems() override { return TICK_SYSTEM;}

    void tick(float seconds) override;

    void setBTNode(std::shared_ptr<BTNode> btNode);

public:
    std::shared_ptr<BTNode> btNode;
};

#endif // AICOMPONENT_H
