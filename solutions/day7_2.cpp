#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

struct Node {
    int x;
    int y;
    Node* left;
    Node* right;
};

//global so anywhere can use it
//convert x, y to row major for key 
std::unordered_map<long long, Node*> nodes;
std::unordered_map<Node*, long long> memo;

int height(Node* root) {
    if (!root) {
        return 0;
    }

    int left = height(root->left);
    int right = height(root->right);

    return 1 + (left > right ? left : right);
}

Node* find_children(Node* node, std::vector<std::string> lines, int dx) {
    if (node->y >= lines.size() - 2) {
        return nullptr;
    }
     
    //dx == -1 finds left child
    //dx == 1 finds right child
    int x = node->x + dx;
    int y = node->y;
    char current_char = '\0';
    while (current_char != '^' && y < lines.size() - 1) {
        y += 1;
        current_char = lines.at(y).at(x);
    }
    
    if (current_char == '^') {
        long long key = x + lines.at(0).size() * y;         
        Node* new_node;
        //if this point is not in nodes
        if (nodes.find(key) == nodes.end()) {
            new_node = new Node{ x, y, nullptr, nullptr };
            nodes.emplace(key, new_node);
            new_node->left = find_children(new_node, lines, -1);
            new_node->right = find_children(new_node, lines, 1);
        } else {
            new_node = nodes.at(key);
        }
        
        return new_node;
    } else {
        return nullptr;
    }
}

long long dfs(Node* node) {
    auto entry = memo.find(node);
    if (entry != memo.end()) {
        return entry->second;
    }

    if (!node) {
        memo[node] = 1;
        return 1;
    }

    long long ans = dfs(node->left) + dfs(node->right);
    memo[node] = ans;
    return ans;
}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day7.txt");
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line)) {
        lines.push_back(line); 
    }
    
    Node* root = nullptr;

    // construct tree
    for (int i = 2; i < lines.size(); i++) {
        for (int j = 0; j < lines.at(i).length(); j++) {
            if (root == nullptr && lines.at(i).at(j) == '^') {
                root = new Node{ j, i, nullptr, nullptr };
                root->left = find_children(root, lines, -1);
                root->right = find_children(root, lines, 1);
            }
        }
    } 
    
    //DFS
    long long total_timelines = dfs(root);
    std::cout << total_timelines << "\n";
    
}
