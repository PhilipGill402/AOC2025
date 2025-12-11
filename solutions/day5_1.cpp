#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

typedef struct range_t {
    long long start;
    long long stop;
} range_t;

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day5.txt");
    std::vector<range_t> ranges;
    int total = 0;

    std::string line;
    getline(file, line);
    
    //parse ranges
    while (line != "") { 
        std::stringstream str_stream(line);
        std::string start_str;
        std::string end_str;
        getline(str_stream, start_str, '-');
        getline(str_stream, end_str, '-');
        
        range_t range;
        range.start = stoll(start_str);
        range.stop = stoll(end_str);

        ranges.push_back(range);
             
        getline(file, line);
    } 

    //parse ids
    while (getline(file, line)) {
        long long id = stoll(line); 
        for (range_t range: ranges) {     
            if (id >= range.start && id <= range.stop) {
                total++;
                break;
            }
        }    
    }

    std::cout << total << "\n";
}
