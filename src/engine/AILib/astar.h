#ifndef ASTAR_H
#define ASTAR_H

#include "engine/util/CommonIncludes.h"
#include <QGLWidget>

template <class N>
class AStar{
public:
    void findPath(std::shared_ptr<QList<std::shared_ptr<N>>> path,
                  std::shared_ptr<N> start,
                  std::shared_ptr<N> end,
                  std::function<float(std::shared_ptr<N>)> heuristic,
                  float (*distance)(std::shared_ptr<N>, std::shared_ptr<N>),
                  std::shared_ptr<QList<std::shared_ptr<N>>> (*adjacent)(std::shared_ptr<N>));

};

#endif // ASTAR_H
