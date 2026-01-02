#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct vec3 {
    int x;
    int y;
    int z;

    bool operator==(const vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    std::string to_string() {
        std::string str = "<";
        str += std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ">";
        return str;  
    } 
};

struct Edge {
    vec3 box_a;
    vec3 box_b;
    long long distance;
};

long long distance(vec3 vec_a, vec3 vec_b) {
    long long dx = (long long)vec_a.x - (long long)vec_b.x;
    long long dy = (long long)vec_a.y - (long long)vec_b.y;
    long long dz = (long long)vec_a.z - (long long)vec_b.z;
    return dx*dx + dy*dy + dz*dz;
}

bool comparator(Edge edge_a, Edge edge_b) {
    return edge_a.distance < edge_b.distance;
}

bool size_comparator(std::vector<vec3> circuit_a, std::vector<vec3> circuit_b) {
    return circuit_a.size() > circuit_b.size();
}

std::vector<Edge> generate_edges(std::vector<vec3> boxes) {
    std::vector<Edge> edges;
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i+1; j < boxes.size(); j++) {
            edges.push_back({ boxes.at(i), boxes.at(j), distance(boxes.at(i), boxes.at(j)) });
        }
    } 

    return edges;
}

int get_circuit_index(std::vector<std::vector<vec3>>& circuits, vec3 box) {
    for (int i = 0; i < circuits.size(); i++) {
        if (find(circuits.at(i).begin(), circuits.at(i).end(), box) != circuits.at(i).end()) {
            return i;
        }
    }

    return -1;
}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day8.txt");
    std::string line;
    std::vector<vec3> boxes;
    
    vec3 pos;
    while (getline(file, line)) {
        std::stringstream line_stream(line); 
        std::string x;
        std::string y;
        std::string z;
        getline(line_stream, x, ',');
        getline(line_stream, y, ',');
        getline(line_stream, z, ',');
        
        pos = { stoi(x), stoi(y), stoi(z) };
        boxes.push_back(pos);
    }
    
    std::vector<Edge> edges = generate_edges(boxes);
    sort(edges.begin(), edges.end(), comparator);

    std::vector<std::vector<vec3>> circuits;
     
    for (int i = 0; i < 1000; i++) {
        Edge edge = edges.at(i);

        int index_a = get_circuit_index(circuits, edge.box_a);
        int index_b = get_circuit_index(circuits, edge.box_b);
        
        if (index_a == -1 && index_b == -1) {
            //no circuits contain either box 
            circuits.push_back({ edge.box_a, edge.box_b });
        } else if (index_a != -1 && index_b == -1) {
            //box a is in a circuit
            if (find(circuits.at(index_a).begin(), circuits.at(index_a).end(), edge.box_b) == circuits.at(index_a).end()) {
                circuits.at(index_a).push_back(edge.box_b);
            }
        } else if (index_a == -1 && index_b != -1) {
            //box b is in a circuit
            if (find(circuits.at(index_b).begin(), circuits.at(index_b).end(), edge.box_a) == circuits.at(index_b).end()) {
                circuits.at(index_b).push_back(edge.box_a);
            }
        } else {

            //both are in the same circuit
            if (index_a == index_b) {
                continue;
            }
            

            if (index_a > index_b) {
                std::swap(index_a, index_b);
            } 

            //if not then merge circuits
            for (auto& box : circuits.at(index_b)) {
                if (find(circuits.at(index_a).begin(), circuits.at(index_a).end(), box) == circuits.at(index_a).end()) {
                    circuits.at(index_a).push_back(box);
                }
            }

            circuits.erase(circuits.begin() + index_b);
        }
    }
    
    sort(circuits.begin(), circuits.end(), size_comparator); 
    
    /*
    for (std::vector<vec3> circuit : circuits) {
        for (vec3 box : circuit) {
            std::cout << box.to_string() << "\n";
        }

        std::cout << "\n";
    }
    */
    
    std::cout << circuits.at(0).size() << "\n";
    std::cout << circuits.at(1).size() << "\n";
    std::cout << circuits.at(2).size() << "\n";


    long long result = circuits.at(0).size() * circuits.at(1).size() * circuits.at(2).size();

    std::cout << result << "\n";
}
