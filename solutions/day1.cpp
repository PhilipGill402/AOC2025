#include <fstream>
#include <iostream>

int count_zeros (int curr_pos, int turns, char dir) {
    int counter = 0;
    std::cout << "Pos: " << curr_pos << "\nTurns: " << turns << "\n";
    while (turns - 100 > 0) {
        turns -= 100;
        counter += 1;    
    }
    
    if (dir == 'L') {
        std::cout << "New Pos: " << ((((curr_pos - turns) % 100) + 100) % 100) << "\n";
    } else if (dir == 'R') {
        std::cout << "New Pos: " << ((((curr_pos + turns) % 100) + 100) % 100) << "\n";
    }

    if (dir == 'L' && curr_pos - turns <= 0 && curr_pos != 0) {
        counter++;
    } else if (dir == 'R' && curr_pos + turns >= 100 && curr_pos != 0) {
        counter++;
    }
    
    std::cout << "Counter: " << counter << "\n\n";

    return counter;
}

int main() {
    std::fstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day1.txt", std::ios::in);
    std::string line;
    int pos = 50;
    int counter = 0;

    while (file >> line) {
        char dir = line[0];
        int turns = stoi(line.substr(1, line.size() - 1));
        counter += count_zeros(pos, turns, dir); 

        if (dir == 'L') {
            pos = (((pos - turns) % 100) + 100) % 100;
        } else if (dir == 'R') {
            pos = (((pos + turns) % 100) + 100) % 100;
        } else {
            std::cout << "unsupported\n";
        }
    }

    std::cout << counter << '\n';

    return 0;
}
