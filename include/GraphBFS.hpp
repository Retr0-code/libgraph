#pragma once
#include "GraphBase.hpp"
#include "Accumulators.hpp"

#include <queue>
#include <unordered_map>
#include <unordered_set>

template <class T>
class GraphBFS : public IGraphUnweighted<T> {
public:
    using VertexId = uint32_t;

    virtual IGraphUnweighted<T>& EdgeAdd(VertexId from, VertexId to, bool bidirectional = false);

    virtual Path<T> Traverse(
        VertexId from,
        VertexId to,
        const AccumulatorPtr<T> & accumulator);

private:
    using Vertex = std::unordered_set<VertexId>;

    std::unordered_map<VertexId, Vertex> _graph;
};

template <class T>
IGraphUnweighted<T>& GraphBFS<T>::EdgeAdd(VertexId from, VertexId to, bool bidirectional) {
    this->_graph[from].emplace(to);

    if (bidirectional)
        this->_graph[to].emplace(from);

    return *this;
}

template <class T>
Path<T> GraphBFS<T>::Traverse(VertexId from, VertexId to, const AccumulatorPtr<T> &accumulator) {
    Path<T> shortestPath;
    std::unordered_map<VertexId, bool> visited;
    std::unordered_map<VertexId, VertexId> parent;
    std::queue<VertexId> queueLayer;

    queueLayer.push(from);
    parent[from] = from;
    while (!queueLayer.empty()) {
        VertexId root = queueLayer.front();
        queueLayer.pop();

        if (to == root) {
            History<T> history;
            for (VertexId v = to; v != from; v = parent[v])
                history.push_front(VertexStatus{v, 0});
            
            history.push_front(VertexStatus{from, 0});
                
            shortestPath = history;
            break;
        }

        if (!visited[root])
            visited[root] = true;

        for (VertexId vertex : this->_graph[root]) {
            if (visited[vertex])
                continue;

            visited[vertex] = true;
            queueLayer.push(vertex);
            parent[vertex] = root;
        }
    }
    return shortestPath;
}
