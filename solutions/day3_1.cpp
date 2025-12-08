#include <iostream>
#include <fstream>
#include <sstream>

int* find_max(std::string line, int start_index, int exclude_index) {
    int* ret = new int[2]; 
    
    if (start_index >= line.length()) {
        return nullptr;
    }

    int max = line[start_index] - '0';
    int max_idx = start_index;

    for (int i = start_index + 1; i < line.length(); i++) {
        int curr_num = line[i] - '0';

        if (curr_num > max && i != exclude_index) {
            max = curr_num;
            max_idx = i;
        }
    }
    
    ret[0] = max_idx;
    ret[1] = max;

    return ret;
}

bool is_last(std::string line, int num) {
    for (int i = 0; i < line.length(); i++) {
        int curr_num = line[i] - '0'; 
        
        if (i == line.length() - 1 && curr_num == num) {
            return true;
        }

        if (curr_num == num) {
            return false;
        }
    }

    return false;

}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day3.txt");
    std::string line;
    int total = 0;

    while (getline(file, line)) {
        int second;
        int joltage;
        int* ret = find_max(line, 0, -1);
        int max_idx = ret[0];
        int max = ret[1];
        
        if (is_last(line, max)) {
            ret = find_max(line, 0, line.length() - 1);
            second = ret[1];

            joltage = stoi(std::to_string(second) + std::to_string(max));
        } else {
            ret = find_max(line, max_idx + 1, -1);
            second = ret[1];

            joltage = stoi(std::to_string(max) + std::to_string(second));
        }
        
        total += joltage;    
    }

    std::cout << total << "\n";

    
} 
