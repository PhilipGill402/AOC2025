#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void print_vector(std::vector<std::string> vec) {
    for (std::string line : vec) {
        std::cout << line << "\n";
    }
}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day7.txt");
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line)) {
        lines.push_back(line); 
    }

    //loop through lines starting at the second one
    int num_splits = 0;
    for (int i = 1; i < lines.size(); i++) {
        for (int j = 0; j < lines.at(i).length(); j++) {
            char current_char = lines.at(i).at(j);
            char char_above = lines.at(i - 1).at(j);

            if (current_char == '^') {
                if (char_above == '|') {
                    num_splits++; 
                    if (j - 1 >= 0) {
                        lines.at(i).at(j - 1) = '|';
                    }
                    if (j + 1 < lines.at(i).length()) {
                        lines.at(i).at(j + 1) = '|';
                    }
                }
            } else if (char_above == '|') {
                lines.at(i).at(j) = '|';
            } else if (char_above == 'S') {
                lines.at(i).at(j) = '|'; 
            }
        }
         
    }

    std::cout << num_splits << "\n";
}
