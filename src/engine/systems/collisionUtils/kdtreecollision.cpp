#include "kdtreecollision.h"
#include <algorithm>
#include <cmath>

#include <QDebug>

#include "engine/shapes/mesh.h"

template <class T>
auto getComparison(int axis){
    return [axis](const std::shared_ptr<KDTreePoint<T>> p1, const std::shared_ptr<KDTreePoint<T>> p2) -> bool {
        return p1->point[axis] < p2->point[axis];
    };
}

template <class T>
auto getDistanceSort(glm::vec3 p){
    return [p](const std::shared_ptr<KDTreePoint<T>> p1, const std::shared_ptr<KDTreePoint<T>> p2) -> bool {
        return glm::length2(p - p1->point) < glm::length2(p - p2->point);
    };
}

template <class T>
KDTreePoint<T>::KDTreePoint(glm::vec3 point, std::shared_ptr<T> obj){
    this->point = point;
    this->obj = obj;
}

template <class T>
void KDTreePoint<T>::updatePosition(glm::vec3 newPos){
    point = newPos;
}


template <class T>
KDTreeNode<T>::KDTreeNode(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> points, int axis){
    this->size = points->length();
    this->axis = axis;

    if(this->size == 1){
        this->point = points->at(0);
        this->pivot = this->point->point[axis];
        this->min = this->point->point[axis];
        this->max = this->point->point[axis];
        return;
    }

    std::sort(points->begin(), points->end(), getComparison<T>(axis));
    int m = points->length()/2;
    this->point = points->at(m);

//    pivot = 0;
//    for(int i = 0; i < size; i++) pivot += points->at(i)->point[axis];
//    pivot = pivot / size;
//    for(m = 0; points->at(m)->point[axis] < pivot; m++);
//    point = points->at(m);

    this->pivot = this->point->point[axis];
    this->min = points->at(0)->point[axis];
    this->max = points->at(this->size-1)->point[axis];

    if(m > 0){
        QList<std::shared_ptr<KDTreePoint<T>>> l = points->mid(0, m);
        std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> l_ptr = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>(l);
        this->left = std::make_shared<KDTreeNode<T>>(l_ptr, (axis + 1) % 3);
    }

    if( m+1 < this->size){
        QList<std::shared_ptr<KDTreePoint<T>>> r = points->mid(m+1);
        std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> r_ptr = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>(r);
        this->right = std::make_shared<KDTreeNode<T>>(r_ptr, (axis + 1) % 3);
    }
}
template <class T>
void KDTreeNode<T>::addPoint(std::shared_ptr<KDTreePoint<T>> point){
    if(point->point[this->axis] < this->pivot){
        if(this->left == nullptr){
            std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> l_ptr = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>();
            l_ptr->append(point);
            this->left = std::make_shared<KDTreeNode<T>>(l_ptr, (this->axis + 1) % 3);
        } else {
            this->left->addPoint(point);
        }
    } else {
        if(this->right == nullptr){
            std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> r_ptr = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>();
            r_ptr->append(point);
            this->right = std::make_shared<KDTreeNode<T>>(r_ptr, (this->axis + 1) % 3);
        } else {
            this->right->addPoint(point);
        }
    }
}

template <class T>
void KDTreeNode<T>::getPoints(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> list){
    list->append(point);
    if(left) left->getPoints(list);
    if(right) right->getPoints(list);
}

template <class T>
void KDTreeNode<T>::getNearestK(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> relevantPoints, glm::vec3 p, int k){
    std::shared_ptr<QList<std::shared_ptr<KDTreeNode<T>>>> parents = std::make_shared<QList<std::shared_ptr<KDTreeNode<T>>>>();

    if((this->left == nullptr) && (this->right == nullptr)){
        if(!relevantPoints->contains(this->point)) relevantPoints->append(this->point);
        std::sort(relevantPoints->begin(), relevantPoints->end(), getDistanceSort<T>(p));
        while(relevantPoints->length() > k) relevantPoints->pop_back();
        return;
    }

    std::shared_ptr<KDTreeNode<T>> n = nullptr;

    if(p[this->axis] < this->pivot){
        n = this->left;
    } else {
        n = this->right;
    }


    while(n != nullptr){
        parents->append(n);
        if(p[n->axis] < n->pivot){
            n = n->left;
        } else {
            n = n->right;
        }
    }


    for(int i = parents->length() - 1; i >= 0; i--){
        std::shared_ptr<KDTreeNode<T>> parent = parents->at(i);

        if(!relevantPoints->contains(parent->point)) relevantPoints->append(parent->point);
        std::sort(relevantPoints->begin(), relevantPoints->end(), getDistanceSort<T>(p));
        while(relevantPoints->length() > k) relevantPoints->pop_back();

        float d = glm::length2(relevantPoints->last()->point - p);

        if((p[parent->axis] - parent->pivot)*(p[parent->axis] - parent->pivot) < d){
            if(p[parent->axis] < parent->pivot && parent->right != nullptr){
                parent->right->getNearestK(relevantPoints, p, k);
            } else if(p[parent->axis] >= parent->pivot && parent->left != nullptr){
                parent->left->getNearestK(relevantPoints, p, k);
            }
        }
    }

    if(!relevantPoints->contains(this->point)) relevantPoints->append(this->point);
    std::sort(relevantPoints->begin(), relevantPoints->end(), getDistanceSort<T>(p));
    while(relevantPoints->length() > k) relevantPoints->pop_back();

    float d = glm::length2(relevantPoints->last()->point - p);

    if((p[this->axis] - this->pivot)*(p[this->axis] - this->pivot) < d){
        if(p[this->axis] < this->pivot && this->right != nullptr){
            this->right->getNearestK(relevantPoints, p, k);
        } else if(p[this->axis] >= this->pivot && this->left != nullptr){
            this->left->getNearestK(relevantPoints, p, k);
        }
    }

//    std::sort(relevantPoints->begin(), relevantPoints->end(), getDistanceSort<T>(p));
//    while(relevantPoints->length() > k) relevantPoints->pop_back();
}


template <class T>
KDTreeCollision<T>::KDTreeCollision(std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> points){
    this->points = points;
    root = std::make_shared<KDTreeNode<T>>(points, 0);
}

template <class T>
void KDTreeCollision<T>::addPoint(std::shared_ptr<KDTreePoint<T>> point){
    root->addPoint(point);
}

template <class T>
void KDTreeCollision<T>::rebuildSubtree(glm::vec3 origPos, glm::vec3 newPos){
    std::shared_ptr<KDTreeNode<T>> n_parent = nullptr;
    std::shared_ptr<KDTreeNode<T>> n = root;
    bool n_direction = true; // true is left, false is right

    while(n->left and n->right){
        bool b1 = (origPos[n->axis] < n->pivot);
        bool b2 = (newPos[n->axis] < n->pivot);
        if(b1 == b2){
            n_parent = n;
            n_direction = b1;
            if(b1){
                n = n->left;
            } else {
                n = n->right;
            }
        } else {
            break;
        }
    }

    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> relevantPoints = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>();
    for(std::shared_ptr<KDTreePoint<T>> p: *points){
        if(n->min <= p->point[n->axis] and p->point[n->axis] <= n->max)
            relevantPoints->append(p);
    }
    if(n_direction){
        n_parent->left = std::make_shared<KDTreeNode<T>>(relevantPoints, n->axis);
    } else {
        n_parent->right = std::make_shared<KDTreeNode<T>>(relevantPoints, n->axis);
    }
}


template <class T>
std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> KDTreeCollision<T>::nearestK(glm::vec3 p, int k){
    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> relevantPoints = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>();
    root->getNearestK(relevantPoints, p, k);
    return relevantPoints;
}

template <class T>
std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> KDTreeCollision<T>::collideBox(glm::vec3 p, glm::vec3 d){
    std::shared_ptr<KDTreeNode<T>> n = root;
    while(true){
        if(n->left && n->left->min < p[n->axis] && (p+d)[n->axis]< n->left->max){
            n = n->left;
        } else if (n->right && n->right->min < p[n->axis] && (p+d)[n->axis] < n->right->max){
            n = n->right;
        } else {
            break;
        }
    }

    std::shared_ptr<QList<std::shared_ptr<KDTreePoint<T>>>> relevantPoints = std::make_shared<QList<std::shared_ptr<KDTreePoint<T>>>>();
    n->getPoints(relevantPoints);
    return relevantPoints;
}

template class KDTreePoint<Triangle>;
template class KDTreeNode<Triangle>;
template class KDTreeCollision<Triangle>;



