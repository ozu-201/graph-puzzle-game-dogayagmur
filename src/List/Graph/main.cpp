#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"

int main() {
    std::string filePath = R"(C:\Users\yagmu\Downloads\english-dictionary.txt)";

    // Open the file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    // Read 3-lettered words from the file
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        // Check if the word has exactly 3 letters
        if (word.length() == 3) {
            words.push_back(word);
        }
    }
    file.close();

    // Create a graph and build it from the dictionary
    list::Graph graph(words.size());
    graph.buildGraphFromDictionary(words);

    // Find the shortest path between "cat" and "dog"
    graph.shortestPathBetweenWords("cat", "dog");

    return 0;
}
