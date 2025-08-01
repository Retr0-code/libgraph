/*
    Copyright (C) 2023 Nikita Retr0-code Korneev

    libgraph is free software: you can redistribute, modify it
    under the terms of the MIT License.

    You should have received a copy of MIT License along with jsast.js.
    If not, see <https://opensource.org/license/MIT.
*/

#pragma once
#include <list>
#include <vector>
#include <memory>
#include <cstdint>

/**
 * @brief Interface class for accumulation when traversing through graph.
 * 
 * @tparam T - template class for accumulation of some kind.
 */
template <class T>
class IAccumulator {
public:
    virtual const T& operator()(const T& accumulated, const T& value) = 0;

    virtual const T& Get(void) const = 0;
};

using VertexId = uint32_t;

template <class T>
using VertexStatus = std::pair<VertexId, T>;

template <class T>
struct HashVertexStatus {
    std::size_t operator()(const VertexStatus<T>& vertex) const noexcept {
        return std::hash<VertexId>{}(vertex.first);
    }
};

template <class T>
using History = std::list<VertexStatus<T>>;

template <class T>
using AccumulatorPtr = std::shared_ptr<IAccumulator<T>>;

/**
 * @brief Class describing some path in a graph
 * 
 * @tparam T - template of type returned by Accumulator (at least it must has conversion to it).
 */
template <class T>
class Path {
public:
    using PathRaw = std::vector<VertexId>;

    Path(void) : _vertices(), _accumulated(0) {}

    Path(const History<T>& history)
        : _vertices(), _accumulated(history.back().second) {
        for (const VertexStatus<T>& v : history)
            this->_vertices.push_back(v.first);
    }

    /**
     * @brief Amount of vertices.
     * 
     * @return size_t
     */
    size_t Length(void) const {
        return _vertices.size();
    }
    
    const PathRaw& operator()(void) const {
        return _vertices;
    }

    const T& Accumulated(void) const {
        return _accumulated;
    }

private:
    PathRaw _vertices;
    T _accumulated;
};

/**
 * @brief Interface class for different graph representations.
 * 
 * @tparam T - weight type for non-weighted graph it is common to use integer value=1.
 */
template <class T>
class IGraph {
public:
    virtual Path<T> Traverse(
        VertexId from,
        VertexId to,
        const AccumulatorPtr<T>& accumulator) = 0;
};

template <class T>
class IGraphUnweighted : public IGraph<T> {
public:
    virtual IGraphUnweighted<T>& EdgeAdd(VertexId from, VertexId to, bool bidirectional) = 0;
};

template <class T>
class IGraphWeighted : public IGraph<T> {
public:
    virtual IGraphWeighted<T>& EdgeAdd(VertexId from, VertexId to, const T& weight, bool bidirectional) = 0;
};
