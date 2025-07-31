/*
    Copyright (C) 2023 Nikita Retr0-code Korneev

    libgraph is free software: you can redistribute, modify it
    under the terms of the MIT License.

    You should have received a copy of MIT License along with jsast.js.
    If not, see <https://opensource.org/license/MIT.
*/

#include <print>
#include <memory>
#include <iostream>
#include "Accumulators.hpp"
#include "GraphDijkstra.hpp"

int main() {
    GraphDijkstra<int> graph;
    /*
       1--2
      /    \
    0<      4
      \    /
       3--/
     */
    graph.EdgeAdd(0, 1, 25, true)
         .EdgeAdd(1, 2, 37, false)
         .EdgeAdd(0, 3, 12, true)
         .EdgeAdd(2, 4, 46, false)
         .EdgeAdd(3, 4, 20, true);

    AccumulatorPtr<int> acc{reinterpret_cast<IAccumulator<int>*>(new AccumulatorSum<int>(0))};
    Path<int> shortest{graph.Traverse(0, 4, acc)};
    for (VertexId vertex : shortest())
        std::print("{} ", vertex);

    std::print("\nAccumulated: {}\nLength: {}\n", shortest.Accumulated(), shortest.Length());

    return EXIT_SUCCESS;
}