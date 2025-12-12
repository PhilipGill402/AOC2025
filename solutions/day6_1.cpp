#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

#define NUM_LINES 4

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day6.txt");
    std::string line;
    std::vector<std::vector<std::string>> values; 
    
    while (getline(file, line)) {

        int count = 0;
        std::string val;
        for (int i = 0; i < line.length(); ) {
            char c = line.at(i);
            
            if (std::isspace(c)) {
                count++;
                std::cout << val << "\n";
                val.clear();
                
                //skips whitespace
                i++;
                c = line[i];
                //skip remaining whitespace
                while (i < line.length() && std::isspace(line.at(i))) {
                    i++; 
                }
            } else {
                val += c;
                i++;
            }

            
        } 
        
        if (!val.empty()) {
            std::cout << val << "\n";
        }
    }
}
