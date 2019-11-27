#include <iostream> // std::cout, std::cin
#include <algorithm> // std::min
#include <string> // std::string
#include <vector> // std::vector

#define INFINITY 99999999

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

void getD(std::vector<matrix_dim> dimensions, std::vector<int>* D) {
    bool firstRow = true;

    for (int i = 0; i < dimensions.size(); i++ ){
        if (firstRow) {
            D->push_back(dimensions[i].row);
            D->push_back(dimensions[i].column);
            firstRow = false;
        } else {
            D->push_back(dimensions[i].column);
        }
    }
}

// Chain Multiplication Function
int** minmult(int n, const std::vector<int> d) {
     int i, j, k, diag;

    // Declare M,P
    int** M = new int*[n];
    int** P = new int*[n];

    // Initiliate M,P
    for (i = 0; i < n; i ++) {
        M[i] = new int[n];
        M[i][i] = 0;
        P[i] = new int[n];
    }
    
    for (diag = 2; diag < n; diag ++) {
        for (i = 1; i < n - diag + 1; i++) {
            j = i + diag - 1;
            M[i][j] = INFINITY;

            for (k = i; k <= j - 1; k++) {
                int tmp = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
                if (tmp < M[i][j]) {
                    M[i][j] = tmp;
                    P[i][j] = k;
                }
            }
        }
    }

    // Print M
    std::cout << "The following shows the M matrix and the P matrix computed, respectively. \n" << std::endl;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (M[i][j] > 9999) {
                std::cout << "     ";
                continue;
            }
            std::cout << M[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    // Print P
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (P[i][j] > 9999) {
                std::cout << "    ";
                continue;
            }
            std::cout << P[i][j] << "   ";
        }
        std::cout << std::endl;
    }

    return P;
}

void order (int i, int j, int** P) {
    if (i == j) {
        std::cout << "M" << i;
    } else {
        int k = P[i][j];
        std::cout << "(";
        order(i, k, P);
        order(k+1, j, P);
        std::cout << ")";
    }

}

int main() {
    int matrix_num; // matrix number input

    std::vector<matrix_dim> dimensions;
    std::vector<int> D;

    std::string nth[10] = { // String of Nth matrix
        "first", "second", "thrid", "fourth", "fifth",
        "sixth", "seventh", "eighth", "nineth", "tenth"
    };

    do { // User input of total number of matricies
        std::cout << "> Enter the total number of matricies to be multiplied: ";
        std::cin >> matrix_num;
    } while (boundError(matrix_num));

    for (int i = 0; i < matrix_num; i++) { // User input of matrix dimensions
        matrix_dim dim;
        std::cout << "> Enter the dimension for the " << nth[i] << " matrix : ";
        std::cin >> dim.row >> dim.column;
        dimensions.push_back(dim);
    }

    // get vector D
    getD(dimensions, &D);

    int** P = minmult(matrix_num + 1, D);

    std::cout << "The following shows the optimal parenthesization of the matrices. " << std::endl;
    order(1,matrix_num, P);
}