#include <iostream> // std::cout, std::cin
#include <algorithm> // std::min
#include <string> // std::string
#include <vector> // std::vector

struct matrix_dim { // Matrix dimension
    int row;
    int column;
};

// Utility Function
bool boundError(int matrix_num) {
    // the number of matrix should be <10 or >0
    if (matrix_num > 10) {
        std::cout << "[ERROR] Out of bounds, maximum number of matricies is 10" << std::endl;
        return true;
    } else if (matrix_num < 1) {
        std::cout << "[ERROR] Out of bounds, minimum number of matricies is 1" << std::endl;
        return true;
    } else {
        return false;
    }
}

// Chain Multiplication Function
int minmult (int n, const std::vector<int> D, std::vector<std::vector<int>>* M, std::vector<std::vector<int>>* P) {
    int i, j, k, diagonal;

    for (i = 0; i <= n; i++) // All the diagonal of matrix M costs 0 because Ai~Ai is no multiplication
        (*M)[i][i] = 0;

    for (diagonal = 1; diagonal <= n - 1; diagonal ++) {
        for (i = 0; i <= n - diagonal; i++) {
            j = i + diagonal;
            (*M)[i][j] = std::min((*M)[i][k] + (*M)[k+1][j] + D[i-1] * D[k] * D[j]);
            (*P)[i][j] = k;
        }
    }    
}

int main() {
    int matrix_num; // matrix number input
    std::string nth[10] = { // String of Nth matrix
        "first", "second", "thrid", "fourth", "fifth",
        "sixth", "seventh", "eighth", "nineth", "tenth"
    };
    std::vector<matrix_dim> matrix_dimensions; // vector of matrix dimensions

    do { // User input of total number of matricies
        std::cout << "> Enter the total number of matricies to be multiplied: ";
        std::cin >> matrix_num;
    } while (boundError(matrix_num));

    for (int i = 0; i < matrix_num; i ++) { // User input of matrix dimensions
        matrix_dim dim;
        std::cout << "> Enter the dimension for the " << nth[i] << " matrix : ";
        std::cin >> dim.row >> dim.column;
        matrix_dimensions.push_back(dim);
    }

    // // Test matrix dimension output
    // int num = 1;
    // for (matrix_dim tmp: matrix_dimensions) {
    //     std::cout << "Matrix #" << num << "[" << tmp.column << "," << tmp.row << "]" << std::endl;
    //     num ++;
    // }
}