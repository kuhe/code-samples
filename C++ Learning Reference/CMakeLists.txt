cmake_minimum_required(VERSION 3.1)
project(cppRef)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(cppRef ${SOURCE_FILES} "Data Structures/Item.h" Algorithms/GreedyScheduler.cpp Algorithms/GreedyScheduler.h "Data Structures/WeightedJob.cpp" "Data Structures/WeightedJob.h" Algorithms/Prim.cpp Algorithms/Prim.h "Data Structures/Graph/Tree.cpp" "Data Structures/Graph/Tree.h" "Data Structures/Graph/Graph.cpp" "Data Structures/Graph/Graph.h" "Data Structures/Graph/GraphNode.cpp" "Data Structures/Graph/GraphNode.h" "Data Structures/Graph/Edge.cpp" "Data Structures/Graph/Edge.h" Utilities/vector_util.h Utilities/vector_util.cpp "Data Structures/Graph/_graph_common.h" Algorithms/_algo_common.h Utilities/string_util.h Algorithms/_algo_common.h Utilities/string_util.cpp Algorithms/DistanceClustering.cpp Algorithms/DistanceClustering.h Algorithms/Solver.h "Data Structures/Set/DisjointSetStructure.cpp" "Data Structures/Set/DisjointSetStructure.h" "Data Structures/Set/Set.cpp" "Data Structures/Set/Set.h" "Data Structures/Set/_set_common.h")