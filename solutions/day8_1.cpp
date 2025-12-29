#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct vec3 {
    int x;
    int y;
    int z;
    vec3* next;

    bool operator==(const vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    std::string to_string() {
        std::string str = "<";
        str += std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ">";
        return str;  
    } 
};

double distance(vec3 vec_a, vec3 vec_b) {
    return sqrt((vec_a.x - vec_b.x)*(vec_a.x - vec_b.x) + (vec_a.y - vec_b.y)*(vec_a.y - vec_b.y) + (vec_a.z - vec_b.z)*(vec_a.z - vec_b.z));
}


//O(N^2) consider sorting the vector by distance somehow and then finding the lowest distance that way
std::vector<vec3> find_lowest_distance(std::vector<vec3> &boxes, std::vector<vec3> &seen) {
    std::vector<vec3> lowest_distance = { vec3{ 0, 0, 0, nullptr }, vec3{ 0, 0, 0, nullptr } };
    lowest_distance.shrink_to_fit();
    int min_dst = -1;
    for (int i = 0; i < boxes.size(); i++) {
        vec3 box1 = boxes.at(i);
        for (int j = 0; j < boxes.size(); j++) {
            if (i == j) {
                continue;
            }

            vec3 box2 = boxes.at(j);
            double dst = distance(box1, box2);
            if (dst < min_dst || min_dst == -1) {
                
                //need to make sure that these are not in seen
                bool is_contained = false;
                for (int i = 0; i < (int)seen.size() - 1; i += 2) {
                    if ((seen[i] == box1 && seen[i+1] == box2) || (seen[i] == box2 && seen[i+1] == box1)) {
                        is_contained = true;
                        break;
                    }
                }
                
                if (!is_contained) {
                    lowest_distance[0] = box1;
                    lowest_distance[1] = box2;
                    min_dst = dst;
                }
                
            } 
        }
    }
    
    seen.push_back(lowest_distance[0]);
    seen.push_back(lowest_distance[1]);

    return lowest_distance;
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
        
        pos = { stoi(x), stoi(y), stoi(z), nullptr };
        boxes.push_back(pos);
    }
    
    std::vector<vec3> heads;
    std::vector<vec3> seen;
    for (int i = 0; i < 10; i++) {
        std::vector<vec3> lowest = find_lowest_distance(boxes, seen);
        std::cout << lowest[0].to_string() << "\n" << lowest[1].to_string() << "\n";
        
        //if there is no vector in the circuit then make the next vector in the circuit the other lowest vector and add it to the list of circuits
        if (lowest[0].next == nullptr) {
            lowest[0].next = &lowest[1];
            heads.push_back(lowest[0]);
        }
        
        //if there are already vectors in the circuit then go until a vector does not have a next and then add the vector to the end of the list
        vec3 tail = lowest[0];
        while (tail.next != nullptr) {
            tail = *tail.next; 
        }
    }
    
}
