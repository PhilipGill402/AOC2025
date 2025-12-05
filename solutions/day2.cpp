#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day2.txt");
    std::string input;
    getline(file, input);
    std::stringstream str_stream(input);
    
    std::string range;

    long long total = 0;

    while (getline(str_stream, range, ',')) {
        std::stringstream range_stream(range);
        std::string start;
        std::string end;
        getline(range_stream, start, '-');
        getline(range_stream, end, '-');
        
        for (long long pos = stoll(start); pos <= stoll(end); pos++) {
            std::string num = std::to_string(pos);
            long long midpoint = (num.length() / 2) - 1; 
            if (num.length() % 2 == 0 && num.substr(0, num.length() - midpoint - 1) == num.substr(midpoint+1, num.length() - 1)) {
                total += pos; 
            }
        } 

    }
    
    std::cout << "Total: " << total << "\n";
}
