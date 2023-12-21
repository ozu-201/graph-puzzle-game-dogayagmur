//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H


#include <string>
#include <vector>
#include "EdgeList.h"
#include "../../General/AbstractGraph.h"

namespace list {

    class Graph : public AbstractGraph{
    private:
        EdgeList *edges;
        std::vector<std::string> wordList;
        int vertexCount;
    public:
        explicit Graph(int vertexCount);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void connectedComponentsDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(int source);
        void prim();

        void buildGraphFromDictionary(const std::vector<std::string> &dictionary);

        void breadthFirstSearch(bool* visited, int startNode) override;

        void depthFirstSearch(bool* visited, int fromNode) override;

    protected:

        Edge* edgeList(int& edgeCount) override;

        bool areValidEdges(const std::string& word1, const std::string& word2) const;
        int findWordIndex(const std::string& word) const;

    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H