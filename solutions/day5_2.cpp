#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day5.txt");
    
    std::set<long long> ids;

    std::string line;
    getline(file, line);
    
    //parse ranges
    while (line != "") { 
        std::stringstream str_stream(line);
        std::string start_str;
        std::string end_str;
        getline(str_stream, start_str, '-');
        getline(str_stream, end_str, '-');
        
        long long start = stoll(start_str);
        long long stop = stoll(end_str);

        //consider using formula: total += (stop - start) + 1; (PROBLEM: counts numbers multiple times) 

        for (long long i = start; i <= stop; i++) {
            ids.insert(i);
        } 

        getline(file, line);
    }



    std::cout << ids.size() << "\n";
}
