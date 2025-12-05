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
            
            //one digit numbers can't be counted
            if (num.length() == 1) {
                continue;
            }

            for (int length = 1; length <= num.length() - midpoint - 1; length++) {
                //there cannot be an occurence if the length of the number is not divisible by the length of the substring we're trying to find 
                if (num.length() % length != 0) {
                    continue;
                }
                
                int target = stoi(num.substr(0, length));
                bool isValid = true;
                for (int pos = length; pos < num.length(); pos += length) {
                    if (stoi(num.substr(pos, length)) != target) {
                        isValid = false; 
                        break;
                    } 
                }

                if (isValid) {
                    total += stoll(num);
                    //doesnt matter how many we find, just count it once
                    break;
                }
            }
        } 

    }
    
    std::cout << "Total: " << total << "\n";
}
