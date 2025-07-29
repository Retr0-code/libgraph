#pragma once
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
    virtual void operator()(const T& value) = 0;
    
    virtual void operator()(T value) = 0;

    virtual const T& Get(void) = 0;
};

/**
 * @brief Class describing some path in a graph
 * 
 * @tparam TAccumulator - template class for any accumulator.
 */
template <class TAccumulator>
class Path {
public:
    using VertexId = uint32_t;
    using PathRaw = std::vector<VertexId>;
    using AccumulatorPtr = std::shared_ptr<TAccumulator>;

    Path(AccumulatorPtr accumulator);

    /**
     * @brief Amount of vertices.
     * 
     * @return size_t
     */
    size_t Length(void) const;
    
    const PathRaw& operator()(void) const;

private:
    PathRaw _vertices;
    std::shared_ptr<TAccumulator> _accumulator;
    size_t _length;
};

/**
 * @brief Interface class for different graph representations.
 * 
 * @tparam T - weight type for non-weighted graph it is common to use boolean value or just delete this interface function.
 */
template <class T>
class IGraph {
public:
    using VertexId = uint32_t;

    virtual void VertexAdd(VertexId from, VertexId to, const T& weight) = 0;

    virtual Path Traverse(VertexId from, VertexId to) = 0;
};
