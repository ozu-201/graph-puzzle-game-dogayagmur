#include <iostation>
#include <fstation>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map <string,vector<string>> adjList;
    unordered_set <string> uniqueWords;

public:
    void addEdge (const string& word1, const string& word2){
        adjList[word1].push_back(word2);
        adjList[word2].push_back(word1);
    }

    bool validConnection(const string& word1, const string& word2){
        int diffCount = 0;
        for (size_t i = 0; i < word1.lenght(); ++i){
            if(word1[i] != word2[i]){
                if(++diffCount > 1){
                    return false;
                }
            }
        }
        return diffCount == 1;
    }

    void addWords (const string& word){
        uniqueWords.insert(word);
    }

    <vector <string>> getWords() const{
        vector <string> words;
        for (const auto& entry: uniqueWords)
    }
};

void createGraphFromFile(const string& file, Graph graph){

}

