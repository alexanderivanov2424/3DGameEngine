#ifndef BTNODE_H
#define BTNODE_H

#include "engine/util/CommonIncludes.h"
#include <vector>
#include <QGLWidget>

enum Status { SUCCESS, FAIL, RUNNING };

class BTNode{
public:
    virtual Status tick(float seconds) = 0;
    virtual void reset() = 0;
};

class BTCompositeNode : public BTNode{
public:
    BTCompositeNode();

    void reset() override;

    void linkChild(std::shared_ptr<BTNode> child);
    void removeChild(std::shared_ptr<BTNode> child);

    std::shared_ptr<QList<std::shared_ptr<BTNode>>> getChildren();

protected:
    std::shared_ptr<QList<std::shared_ptr<BTNode>>> children;
    int lastRunning = 0;
};


class BTActionNode: public BTNode{
};

class BTConditionNode: public BTNode{
public:
    BTConditionNode();

    Status tick(float seconds) override{
        return checkCondition(seconds) ? SUCCESS : FAIL;
    }

    virtual bool checkCondition(float seconds) = 0;
};

class BTSelectorNode: public BTCompositeNode{
public:
    BTSelectorNode();

    Status tick(float seconds) override;
};


class BTSequenceNode: public BTCompositeNode{
public:
    BTSequenceNode();

    Status tick(float seconds) override;
};

#endif // BTNODE_H
