#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> dfs_spanning_tree(std::vector<std::vector<int>> adjacent_list) {
    std::stack<int> s;
    std::vector<bool> visited(adjacent_list.size(), false);
    std::vector<std::vector<int>> spanning_tree(adjacent_list.size(), std::vector<int>());
    s.push(0);
    visited[0] = true;
    
    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        visited[vertex] = true;

        for (auto neighbor : adjacent_list[vertex]) {
            if (!visited[neighbor]) {
                s.push(neighbor);
                spanning_tree[vertex].push_back(neighbor);
                spanning_tree[neighbor].push_back(vertex);
                visited[neighbor] = true;
            }

        }
    }
    return spanning_tree;
}

std::vector<std::vector<int>> bfs_spanning_tree(std::vector<std::vector<int>> adjacent_list) {
    std::queue<int> q;
    std::vector<std::vector<int>> spanning_tree(adjacent_list.size(), std::vector<int>());
    std::vector<bool> visited(adjacent_list.size(), false);
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        visited[vertex] = true;
        
        for (auto adjacent : adjacent_list[vertex]) {
            if (!visited[adjacent]) {
                q.push(adjacent);
                spanning_tree[vertex].push_back(adjacent);
                spanning_tree[adjacent].push_back(vertex);
                visited[adjacent] = true;
            }
        }
    }

    return spanning_tree;
}

std::vector<std::vector<int>> getGraphList(const char* filename) {
    std::vector<std::vector<int>> result;

    std::fstream file_in(filename, std::ios::in);
    std::string buffer;

    while (getline(file_in, buffer)) {
        
        std::vector<int> adjacent;
        
        std::string temp = "";
        for (int index = 0; index < buffer.length(); index++) {
            if (buffer[index] == ' ' || buffer[index] == '\t') {
                adjacent.push_back(stoi(temp));
                temp = "";
            }
            else {
                temp = temp + buffer[index];
                if (index == buffer.length() - 1)
                    adjacent.push_back(stoi(temp));
            }
        }

        result.push_back(adjacent);
    }

    return result;
}

void print(std::vector<std::vector<int>> adjacent_list) {
    int vertex = 0;
    for (std::vector<int> &adjacent : adjacent_list) {
        std::cout << vertex << ": ";
        for (int &ver : adjacent) {
            std::cout << ver << " ";
        }
        std::cout << "\n";
        vertex++;
    }
    std::cout << "\n";
}

int main() {
    std::vector<std::vector<int>> adjacent_list = getGraphList("graph.txt");
    print(adjacent_list);
    print(dfs_spanning_tree(adjacent_list));
    print(bfs_spanning_tree(adjacent_list));
    return 0;
}