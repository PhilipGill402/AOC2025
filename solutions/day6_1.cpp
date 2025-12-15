#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

#define NUM_LINES 5

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day6.txt");
    std::string line;
    std::vector<std::vector<std::string>> values;
    bool first = true;
    long long total = 0;

    while (getline(file, line)) {
        std::stringstream line_stream(line);
        std::string val;
        int count = 0;

        while (getline(line_stream, val, ' ')) {
            //if the length is 0 then it can't be a value
            if (val.length() < 1) {
                continue;
            }
            
            //if the first character is whitespace then skip
            char first_char = val.at(0);
            if (std::isspace(first_char)) {
                continue;
            }

            if (first) {
                std::vector<std::string> val_vec;
                values.push_back(val_vec);
            }     
        
            values[count].push_back(val);

            count++;
        }

        first = false;
    }

    
    for (std::vector<std::string> col : values) {
        std::string op;
        long long line_total = 0; 
        
        //go backwards so the operator will be first
        for (auto it = col.rbegin(); it != col.rend(); it++) {
            //skip operator 
            if (it == col.rbegin()) {
                if (*it == "*") {
                    line_total++;
                    op = "*";
                } else {
                    op = "+";
                }

                continue;
            } 
            
            std::string val = *it;
            if (op == "*") {
                line_total *= stoll(val);
            } else {
                line_total += stoll(val);
            }
            
        }

        total += line_total;
    }

    std::cout << total << "\n";
}
