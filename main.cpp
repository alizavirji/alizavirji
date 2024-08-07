//
//  main.cpp
//  hw6.3
//
//  Created by Aliza Virji on 3/12/24.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "grid.h"
using namespace std;

int main(int argc, const char * argv[]) {
    //opens input and output files from argv
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    int cols;
    int rows;
    char sign;
    input >> cols >> rows; //goes through first line of input file to get the column and row numbers
    std::vector<std::string> words;
    std::vector<std::string> forbiddenWords;
    std::string word;
    //goes through each line of input for the sign and word, and checks if the sign is positive or negative and adds it to the corresponding vector based on the sign
    while (input >> sign >> word) {
        if (sign == '+') {
            words.push_back(word);
        }
        else if (sign == '-') {
            forbiddenWords.push_back(word);
        }
    }
    
    WordSearch grid(rows, cols); //creates grid class object based on the rows and cols
    //creating the solutions and solution vector for allSolutions and oneSolution
    std::vector<std::vector<std::vector<char>>> solutions;
    std::vector<std::vector<char>> solution;
    std::string numOutputs = argv[3];
    //if user asks for all solutions, calls allSolutions and prints out each of the boards in the corresponding format
    if (numOutputs == "all_solutions") {
        allSolutions(grid, words, 0, forbiddenWords, solutions);
        output << solutions.size() << " solution(s)\n";
        for (size_t i = 0; i < solutions.size(); ++i) {
            output << "Board:\n";
            for (size_t j = 0; j < solutions[i].size(); ++j) {
                output << "  ";
                for (size_t k = 0; k < solutions[i][j].size(); ++k) {
                    output << solutions[i][j][k];
                }
                output << "\n";
            }
        }
    }
    //if user asks for one solution, calls oneSolution, which already prints out the grid in the function
    if (numOutputs == "one_solution"){
        oneSolution(grid, words, 0, forbiddenWords, solution, output);
    }
    return 0;
}
