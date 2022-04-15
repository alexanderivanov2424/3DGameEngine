#include "astar.h"

#include <QMap>

#include <QDebug>

#include "engine/AILib/navmesh.h"

template <class N>
void AStar<N>::findPath(std::shared_ptr<QList<std::shared_ptr<N>>> path,
              std::shared_ptr<N> start,
              std::shared_ptr<N> end,
              std::function<float(std::shared_ptr<N>)> heuristic,
              float (*distance)(std::shared_ptr<N>, std::shared_ptr<N>),
              std::shared_ptr<QList<std::shared_ptr<N>>> (*adjacent)(std::shared_ptr<N>)){


    QList<std::shared_ptr<N>> openSet = QList<std::shared_ptr<N>>();
    openSet.append(start);

    QMap<std::shared_ptr<N>,std::shared_ptr<N>> cameFrom = QMap<std::shared_ptr<N>,std::shared_ptr<N>>();

    QMap<std::shared_ptr<N>, float> gScore = QMap<std::shared_ptr<N>, float>();
    gScore.insert(start, 0);

    QMap<std::shared_ptr<N>, float> fScore = QMap<std::shared_ptr<N>, float>();
    fScore.insert(start, heuristic(start));

    std::shared_ptr<N> current;

    while(openSet.length() > 0){

        current = openSet.at(0);
        for(std::shared_ptr<N> node : openSet){
            if(!openSet.contains(node)) continue;
            if(fScore[node] < fScore[current]) current = node;
        }



        if(current == end){
            break;
        }

        openSet.removeOne(current);
        std::shared_ptr<QList<std::shared_ptr<N>>> neighbors = adjacent(current);

        for(int i = 0; i < neighbors->length(); i++){
            std::shared_ptr<N> neighbor = neighbors->at(i);
            float tentativeScore = gScore[current] + distance(current, neighbor);
            if(!gScore.contains(neighbor) || tentativeScore < gScore[neighbor]){
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeScore;
                fScore[neighbor] = tentativeScore + heuristic(neighbor);
                if(!openSet.contains(neighbor)){
                    openSet.append(neighbor);
                }
            }
        }
    }


    path->push_front(current);
    while(cameFrom.contains(current)){
        current = cameFrom[current];
        path->push_front(current);
    }
}

template class AStar<NavRegion>;
