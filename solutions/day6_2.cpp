#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include<vector>
#include<stack>

int main() {
    std::ifstream file("/Users/philipgill/Developer/c/AOC2025/inputs/day6.txt");
    std::string curr_line;
    std::vector<std::string> lines;
    std::vector<char> operators;
    bool first = true;
    long long total = 0;
    
    //we want to get the last line of operators and in the process we put all the lines in a vector so that they are easily accessible
    while (getline(file, curr_line)) { 
        lines.push_back(curr_line);
    }
    
    //pops the operator line from the list of lines and stores it in a variable
    std::string op_line = lines.at(lines.size() - 1);
    lines.pop_back();

    std::string line;
    std::stack<long long> num_stack;
    //loop over every character in a line in reverse order
    for (int i = lines.at(0).length() - 1; i >= 0; i--) {
        std::vector<char> curr_num; 
        for (int j = 0; j < lines.size(); j++) {
            if (isspace(lines.at(j).at(i))) {
                continue;
            }
            curr_num.push_back(lines.at(j).at(i));
        } 
        
        //there was nothing, skip
        if (curr_num.empty()) {
            continue;
        }

        //creates a number from the current line
        long long num = stoll(std::string(curr_num.begin(), curr_num.end()));
        num_stack.push(num);
        //if the op_line at this point has an operator, we need to apply this operator and then add that to the total
        if (op_line.at(i) == '+') {
            long long line_total = 0; 
            while(!num_stack.empty()) {
                //std::cout << "Adding " << num_stack.top() << "\n";
                line_total += num_stack.top();
                num_stack.pop();
            }
            
            //std::cout << "Line Total: " << line_total << "\n";
            total += line_total;
        } else if (op_line.at(i) == '*') {
            long long line_total = 1;
            while(!num_stack.empty()) {
                if (num_stack.top() == 0) {
                    num_stack.pop(); 
                    continue;
                }

                //std::cout << "Multiply " << num_stack.top() << "\n";
                line_total *= num_stack.top();
                num_stack.pop();
            }

            //std::cout << "Line Total: " << line_total << "\n";
            total += line_total;
        }
    } 

    std::cout << total << "\n";
}
