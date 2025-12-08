#include <fstream>
#include <iostream>

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day4.txt");
    int num_lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    
    //resets back to beginning of file
    file.clear();          
    file.seekg(0, std::ios::beg); 

    std::string line;
    getline(file, line);
    
    std::cout << line << "\n"; 
    int arr[num_lines][line.length()];
    
    int line_no = 0;
    do { 
        for (int i = 0; i < line.length(); i++) {
            char curr_char = line[i];

            if (curr_char == '@') {
                arr[line_no][i] = 1;
            } else {
                arr[line_no][i] = 0;
            }
        }

        line_no++;
    } while (getline(file, line));
}
