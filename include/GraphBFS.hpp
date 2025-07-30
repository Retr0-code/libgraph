#pragma once
#include "GraphBase.hpp"
#include "Accumulators.hpp"

template <class T>
class GraphBFS : public IGraph<T> {
public:
    using VertexId = uint32_t;

    virtual IGraph<T>& EdgeAdd(VertexId from, VertexId to, const T& weight, bool bidirectional = false);

    virtual Path<T> Traverse(
        VertexId from,
        VertexId to,
        const IAccumulator<T>& accumulator);

private:
    
};
