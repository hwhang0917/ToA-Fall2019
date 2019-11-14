#include <iostream> // cin, cout
#include <fstream> // ifstream
#include <vector> // vector
#include <string> // getline

std::string FILE_NAME = "p4data.txt"; // hard coded

/* ====== Utility functions ====== */
bool isContinue(char input) {
    // Checks for the user input
    if ((input == 'y') || (input == 'Y')) {
        return true;
    } if ((input == 'n') || (input == 'N')) {
        return false;
    } else {
        std::cout << "[ERROR] Invalid Input! only [Y/N] are valid!" << std::endl;
        return false;
    }
}

std::vector<int> parsedString(std::string line) {
    // parse given string line into vector of integers
    std::string delimeter = " "; // blank space as delimeter
    std::vector<int> integers; // vector of integers
    int num; // single integer to be stored in vector

    size_t pos = 0;
    do { // continue parsing until NULL
        pos = line.find(delimeter);
        num = std::stoi(line.substr(0, pos));
        integers.push_back(num);
        line.erase(0, pos + delimeter.length());
    } while (pos != std::string::npos);

    return integers;
}

void readAdjFromFile(std::string fileName, std::vector<std::vector<int>>* matrix) {
    // Reads 2D-adjacency matrix from txt file (as vector)
    std::string line; // distance between two vertices
    std::ifstream file(fileName); // open file input stream
    matrix->clear(); // clear matrix

    if (!file) // error if file fails to oepn
        std::cout << "[ERROR] Failed to open file! Please check if \"" << fileName <<"\" exists." << std::endl;

    while (std::getline(file, line)) { // loop until getting all the elements from file
        // std::cout << "[OUT]" << line << std::endl;
        matrix->push_back(parsedString(line));
    }
    file.close(); // close filestream
}

/* ====== Matrix Printing function ====== */
void printMatrix(std::vector<std::vector<int>> matrix)
{
    // print given matrix in console
    std::cout << "     ";
    for (int i = 0; i < matrix.size(); i++)
        std::cout << "[V" << i + 1 << "]  ";
    std::cout << std::endl;

    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << "[V" << i + 1 << "] ";
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] > 9)
                std::cout << " " << matrix[i][j] << "   ";
            else
                std::cout << " " << matrix[i][j] << "    ";
        }
        std::cout << std::endl;
    }
}

/* ====== Floyd functions ====== */
void floyd (int n, 
            const std::vector< std::vector<int> > W, 
            std::vector< std::vector<int> >* D,
            std::vector< std::vector<int> >* P) {
    // creates shortest path
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            (*P)[i][j] = 0;
    
    (*D) = W;

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (((*D)[i][k] + (*D)[k][j]) < ((*D)[i][j])) {
                    (*P)[i][j] = k + 1;
                    (*D)[i][j] = (*D)[i][k] + (*D)[k][j];
                }
            }
        }
    }   
}

void path (int q, int r, std::vector< std::vector<int> >* P) { // TODO: fix path function
    // ouotputs the shortest path from Vq to Vr
    int P_vertex = (*P)[q][r];

    if (P_vertex != 0) {
        path(q, P_vertex, P);
        std::cout << P_vertex << " -> ";
        path(P_vertex, r, P);
    } 
}

/* ====== Main function ====== */
int main() {
    // Adjacency matrix[i][j] shows distance between vertex [i] and vertex[j] (9999 = infinity)
    std::vector< std::vector<int> > adjMatrix; // 2D-adjacency matrix vector
    std::vector< std::vector<int> > D, P; // D matrix and P matrix
    std::vector<int> line; // single line of vectors

    int sourceVert, destVert; // source vertex, destination vertex
    char morePath; // user input to continue program
    readAdjFromFile(FILE_NAME, &adjMatrix); // Get adjacency matrix
    int n = adjMatrix.size(); // number of vertices
    
    P = adjMatrix; // Initiate P matrix vector to be size of [i][j]

    // Creates D matrix and P matrix
    floyd(n, adjMatrix, &D, &P);
    std::cout << "============ D Matrix ============" << std::endl;
    printMatrix(D);
    std::cout << "============ P Matrix ============" << std::endl;
    printMatrix(P);

    do {
        std::cout << "Enter a source vertex and destination vertex: ";
        std::cin >> sourceVert >> destVert;

        // Output Shortest Path
        path(sourceVert-1, destVert-1, &P);

        std::cout << std::endl << "More paths? ";
        std::cin >> morePath;
    } while (isContinue(morePath));

        return 0;
}