#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int* find_max(std::string line, int start_index, int stop_index) {
    //we must set to -1 because this can never occur and because index 0 could be excluded 
    int* ret = new int[2]; 
    int max = -1;
    int max_idx = -1;
    
    //std::cout << "START: " << start_index << "\n";
    //std::cout << "STOP: " << stop_index << "\n";

    for (int i = start_index; i <= stop_index; i++) {
        int curr_num = line[i] - '0';
        
        if (curr_num > max) {
            max = curr_num;
            max_idx = i;
        }
    }

    if (max == -1) {
        std::cout << "SOMETHING WENT WRONG\n";
    }
    
    ret[0] = max_idx;
    ret[1] = max;

    return ret;
}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day3.txt");
    std::string line;
    long long total = 0;

    while (getline(file, line)) {
        std::stringstream joltage;
        int* ret; 
        int start = 0;
        int stop = line.length() - 12;
        int max;
        int max_idx;

        for (int i = 1; i < 13; i++) {
            ret = find_max(line, start, stop);
            max_idx = ret[0];
            max = ret[1];
            
            start = max_idx + 1;
            stop++;

            joltage << max;
        } 

        total += stoll(joltage.str()); 
    
    }

    std::cout << total << "\n";
    
} 
