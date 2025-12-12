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
    
    std::string line;
    getline(file, line);
    std::vector<range_t> ranges;
    long long total = 0;
    
    //parse ranges
    while (line != "") { 
        std::stringstream str_stream(line);
        std::string start_str;
        std::string end_str;
        getline(str_stream, start_str, '-');
        getline(str_stream, end_str);
        
        long long start = stoll(start_str);
        long long stop = stoll(end_str);

        range_t new_range;
        new_range.start = start;
        new_range.stop = stop;


        //consider using formula: total += (stop - start) + 1; (PROBLEM: counts numbers multiple times) 
        
        for (int i = 0; i < ranges.size(); ) {
            range_t range = ranges[i];
            
            //if the new range and old range overlap or touch, then merge them
            if (!(new_range.stop < range.start - 1 || range.stop < new_range.start - 1)) {
                new_range.start = std::min(new_range.start, range.start);
                new_range.stop = std::max(new_range.stop, range.stop);

                total -= (range.stop - range.start) + 1;
                ranges.erase(ranges.begin() + i);
            } else {
                i++;
            }
        }    
        
        ranges.push_back(new_range);
        total += (new_range.stop - new_range.start) + 1;
        getline(file, line);
    }
    


    std::cout << total << "\n";
}
