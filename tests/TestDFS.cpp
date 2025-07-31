#include <print>
#include <memory>
#include <iostream>
#include "GraphDFS.hpp"

int main() {
    GraphDFS<float> graph;
    /*
       1--2
      /    \
    0<      4
      \    /
       3--/
     */
    graph.EdgeAdd(0, 1, 2.5f, true)
         .EdgeAdd(1, 2, 3.7f, false)
         .EdgeAdd(0, 3, 1.2f, true)
         .EdgeAdd(2, 4, 4.6f, false)
         .EdgeAdd(3, 4, 2.0f, true);

    AccumulatorPtr<float> acc{reinterpret_cast<IAccumulator<float>*>(new AccumulatorSum<float>(0.f))};
    Path<float> shortest{graph.Traverse(0, 4, acc)};
    for (VertexId vertex : shortest())
        std::print("{} ", vertex);

    std::print("\nAccumulated: {}\nLength: {}\n", shortest.Accumulated(), shortest.Length());

    return EXIT_SUCCESS;
}