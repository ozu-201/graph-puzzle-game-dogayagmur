//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include <iostream>
#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    // Add Edge between the words from their indexes
    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    // Add edge between the words from the words itself
    void Graph::addEdge(string from, string to) {
        int index1 = findWordIndex(from);
        int index2 = findWordIndex(to);
        Edge* edge = new Edge(index1, index2, 1);
        edges[index1].insert(edge);
    }


    // It checks if two words only have one letter of difference
    bool Graph::areValidEdges(const std::string& word1, const std::string& word2) const {
        // if they have different lengths returns a false
        if (word1.length() != word2.length()) {
            return false;
        }

        int difference = 0;
        for(size_t i = 0; i < word1.length(); ++i){
            if(word1[i] != word2[i]){
                ++difference;
            }
        }

        return difference;
    }

    // It checks the list of words and test if they have valid edges, and if they do it creates a graph from it
    void Graph::buildGraphFromDictionary(const std::vector<std::string>& dictionary) {
        wordList.assign(dictionary.begin(), dictionary.end());

        for (size_t i = 0; i < wordList.size(); ++i){
            for(size_t j = i+1; j < wordList.size(); ++j){
                if(areValidEdges(wordList[i], wordList[j])){
                    addEdge((i), (j));
                    addEdge((j), (i));
                }
            }
        }
    }

    // In a list of words returns the index of the desired word
    int Graph :: findWordIndex(const std:: string& word)const{
        for (size_t i = 0; i < wordList.size(); ++i) {
            if(wordList[i] == word){
                return i;
            }
        }
        return -1;
    }

    Graph::~Graph() {
        delete[] edges;
    }

    // finds the shortest way between two words
    void Graph::shortestPathBetweenWords(const std::string& startWord, const std::string& endWord) {

        // find the indexes of the words in the graph
        int startIndex = findWordIndex(startWord);
        int endIndex = findWordIndex(endWord);

        // if they are not present in the dictionary it returns an error message
        if (startIndex == -1 || endIndex == -1) {
            std::cerr << "Error: Words not found in the dictionary." << std::endl;
            return;
        }

        // finds the shortest path using dijkstra
        Path* shortestPaths = dijkstra(startIndex);

        std::cout << "Shortest Path from " << startWord << " to " << endWord << ": ";

        int current = endIndex;
        while (current != startIndex) {
            std::cout << wordList[current] << " -> ";
            current = shortestPaths[current].previous;
        }

        // Print the starting word
        std::cout << wordList[startIndex] << std::endl;

        // Clean up
        delete[] shortestPaths;
    }

    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
        return shortestPaths;
    }

    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }

}