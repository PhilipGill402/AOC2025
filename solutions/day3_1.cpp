#include <iostream>
#include <fstream>
#include <sstream>

int find_max(std::string line, int start_index, int exclude_index) {
    if (start_index >= line.length()) {
        return -1;
    }

    int max = line[start_index] - '0';

    for (int i = start_index + 1; i < line.length(); i++) {
        int curr_num = line[i] - '0';

        if (curr_num > max && i != exclude_index) {
            max = curr_num;
        }
    }

    return max;
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

    while (getline(file, line)) {
        std::cout << line << "\n";
        int max = find_max(line, 0, -1);
        std::cout << is_last(line, max) << "\n";
         
    }
} 
