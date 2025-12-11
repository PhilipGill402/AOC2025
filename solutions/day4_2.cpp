#include <fstream>
#include <iostream>
#include <vector>

int max_rows = 0;
int max_cols = 0;

int count_neighbors(int* arr, int row, int col) {
    int total = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

             
            int new_row = row + i;
            int new_col = col + j;

            if (new_row < 0 || new_row >= max_rows) {
                continue;
            } else if (new_col < 0 || new_col >= max_cols) {
                continue;
            }

            int index = (new_row * max_cols) + new_col; 

            if (arr[index] == 1) {
                total++;
            }
        }
    }

    return total;
}

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day4.txt");
    int num_lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    
    //resets back to beginning of file
    file.clear();          
    file.seekg(0, std::ios::beg); 

    std::string line;
    getline(file, line);
    
    max_rows = num_lines;
    max_cols = line.length();
    int* arr = new int[max_rows * max_cols];
    std::vector<int> indices_to_remove;
    
    int line_no = 0;
    do { 
        for (int i = 0; i < line.length(); i++) {
            int index = (line_no * max_cols) + i;
            char curr_char = line[i];

            if (curr_char == '@') {
                arr[index] = 1;
            } else {
                arr[index] = 0;
            }
        }

        line_no++;
    } while (getline(file, line));
    
    int total = 0;
    int curr_total;
    
    do {
        curr_total = 0;
        for (int row = 0; row < max_rows; row++) {
            for (int col = 0; col < max_cols; col++) {
                int index = (row * max_cols) + col;
                int neighbors = 0;

                if (arr[index] == 1) {

                    neighbors = count_neighbors(arr, row, col);
                
                    if (neighbors < 4) {
                        total++;
                        curr_total++;
                        indices_to_remove.push_back(index);
                    } 
                }
            }
        }

        for (int index : indices_to_remove) {
            arr[index] = 0;
        }

        indices_to_remove.clear();
        
    } while (curr_total > 0);

    std::cout << total << "\n";
}
