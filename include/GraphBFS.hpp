#pragma once
#include "GraphBase.hpp"
#include "Accumulators.hpp"

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
    private:
    struct Vertex {
        // VertexId is adjacent vertex and T is a weight type
        using Edge = std::pair<VertexId, T>;
        
        struct HashEdge {
            std::size_t operator()(const Edge& edge) const noexcept {
                return std::hash<VertexId>{}(edge.first);
            }
        };

        std::unordered_set<Edge, HashEdge> adjacent;
    };

    std::unordered_map<VertexId, Vertex> _graph;
};

template <class T>
IGraphUnweighted<T>& GraphBFS<T>::EdgeAdd(VertexId from, VertexId to, bool bidirectional) {
    this->_graph[from].adjacent.emplace(to, weight);

    if (bidirectional)
        this->_graph[to].adjacent.emplace(from, weight);

    return *this;
}

template <class T>
Path<T> GraphBFS<T>::Traverse(VertexId from, VertexId to, const AccumulatorPtr<T> &accumulator) {
    Path<T> shortestPath;
    std::unordered_map<VertexId, bool> visited;
    History<T> history;
    bool firstEntry{true};

    history.push_back(VertexStatus{from, accumulator->Get()});
    while (!history.empty()) {
        auto [root, accumulated] = history.back();

        // To prevent loops
        if (!visited[root])
            visited[root] = true;

        bool end = true;
        for (auto [vertex, weight] : this->_graph[root].adjacent) {
            if (visited[vertex])
                continue;

            history.push_back(VertexStatus{vertex, (*accumulator)(accumulated, weight)});
            end = false;
            break;
        }
        
        if (to == root) {
            if (firstEntry || accumulated < shortestPath.Accumulated()) {
                shortestPath = history;
                firstEntry = false;
            }
        }

        if (end)
            history.pop_back();
    }
    return shortestPath;
}
