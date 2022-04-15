#ifndef KDTREECOLLISION_H
#define KDTREECOLLISION_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

template <class T> class KDTreeNode;
template <class T> class KDTreeCollision;

template <class T>
class KDTreePoint{
public:
    KDTreePoint(glm::vec3 point, std::shared_ptr<T> obj);

    void updatePosition(glm::vec3 newPos);

public:
    glm::vec3 point;
    std::shared_ptr<T> obj;
};

template <class T>
class KDTreeNode{
public:
    KDTreeNode(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> points, int axis);

    void getPoints(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> list);

    void getNearestK(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> relevantPoints, glm::vec3 p, int k);

    void addPoint(std::shared_ptr<KDTreePoint<T>> point);
public:
    int size;
    int axis = 0;
    float pivot;
    float min;
    float max;

    std::shared_ptr<KDTreePoint<T>> point;
    std::shared_ptr<KDTreeNode<T>> left = nullptr;
    std::shared_ptr<KDTreeNode<T>> right = nullptr;
};


template <class T>
class KDTreeCollision{
public:
    KDTreeCollision(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> points);


    void addPoint(std::shared_ptr<KDTreePoint<T>> point);
    void rebuildSubtree(glm::vec3 origPos, glm::vec3 newPos);
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> nearestK(glm::vec3 p, int K);
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> collideBox(glm::vec3 p, glm::vec3 d);

private:
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> points;
    std::shared_ptr<KDTreeNode<T>> root;

};

#endif // KDTREECOLLISION_H
