#pragma once
#include "GraphBase.hpp"

#include <queue>
#include <vector>
#include <unordered_map>

template <class T>
class GraphDijkstra : public IGraphWeighted<T> {
public:
    public:
    using VertexId = uint32_t;

    virtual IGraphWeighted<T>& EdgeAdd(VertexId from, VertexId to, const T& weight, bool bidirectional = false);

    virtual Path<T> Traverse(
        VertexId from,
        VertexId to,
        const AccumulatorPtr<T>& accumulator);

private:
    using Vertex = std::unordered_map<VertexId, T>;

    std::unordered_map<VertexId, Vertex> _graph;
};

template <class T>
IGraphWeighted<T>& GraphDijkstra<T>::EdgeAdd(VertexId from, VertexId to, const T &weight, bool bidirectional) {
    this->_graph[from][to] = weight;

    if (bidirectional)
        this->_graph[to][from] = weight;

    return *this;
}

template <class T>
Path<T> GraphDijkstra<T>::Traverse(VertexId from, VertexId to, const AccumulatorPtr<T> &accumulator) {
    Path<T> shortestPath;
    std::unordered_map<VertexId, T> distances;
    std::unordered_map<VertexId, VertexStatus<T>> parent;

    using VertexDistance = std::pair<T, VertexId>;
    std::priority_queue<VertexDistance, std::vector<VertexDistance>, std::greater<>> queueLayer;

    for (const auto& [vertex, _] : this->_graph)
        distances[vertex] = std::numeric_limits<T>::max();

    distances[from] = 0;
    parent[from] = VertexStatus<T>{from, 0};

    queueLayer.emplace(0, from);
    while (!queueLayer.empty()) {
        auto [rootDistance, root] = queueLayer.top();
        queueLayer.pop();

        if (to == root) {
            History<T> history;
            for (VertexStatus<T> v = {to, 0}; v.first != from; v = parent[v.first])
                history.push_front(v);
            
            history.push_front(VertexStatus<T>{from, 0});
            history.back().second = std::prev(std::prev(history.end()))->second;

            shortestPath = history;
            break;
        }

        if (rootDistance > distances[root])
            continue;

        for (const auto& [vertex, weight] : this->_graph[root]) {
            T newDistance = (*accumulator)(rootDistance, weight);
            if (newDistance >= distances[vertex])
                continue;

            distances[vertex] = newDistance;
            queueLayer.emplace(newDistance, vertex);
            parent[vertex] = VertexStatus<T>{root, newDistance};
        }
    }
    return shortestPath;
}
