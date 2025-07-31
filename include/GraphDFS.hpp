/*
    Copyright (C) 2023 Nikita Retr0-code Korneev

    libgraph is free software: you can redistribute, modify it
    under the terms of the MIT License.

    You should have received a copy of MIT License along with jsast.js.
    If not, see <https://opensource.org/license/MIT.
*/

#pragma once
#include <utility>
#include <unordered_map>
#include <unordered_set>

#include "GraphBase.hpp"
#include "Accumulators.hpp"

template <class T>
class GraphDFS : public IGraphWeighted<T> {
public:
    using VertexId = uint32_t;

    virtual IGraphWeighted<T>& EdgeAdd(VertexId from, VertexId to, const T& weight, bool bidirectional = false);

    virtual Path<T> Traverse(
        VertexId from,
        VertexId to,
        const AccumulatorPtr<T>& accumulator);

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
IGraphWeighted<T>& GraphDFS<T>::EdgeAdd(VertexId from, VertexId to, const T &weight, bool bidirectional) {
    this->_graph[from].adjacent.emplace(to, weight);

    if (bidirectional)
        this->_graph[to].adjacent.emplace(from, weight);

    return *this;
}

template <class T>
Path<T> GraphDFS<T>::Traverse(VertexId from, VertexId to, const AccumulatorPtr<T> &accumulator) {
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
