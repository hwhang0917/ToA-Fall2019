#include <iostream>
#include <stdexcept>

char FILE_NAME[] = "p4data.txt"; // hard coded

/* ====== Utility function ====== */
bool isContinue(char input) {
    // Checks for the user input
    if ((input == 'y') || (input == 'Y')) {
        std::cout << "Hi" << std::endl;
        return true;
    } if ((input == 'n') || (input == 'N')) {
        std::cout << "Ho" << std::endl;
        return false;
    } else {
        std::cout << "[ERROR] Invalid Input! only [Y/N] are valid!" << std::endl;
        return true;
    }
}

/* ====== Main function ====== */
int main() {
    int sourceVertex, destinationVertex;
    char morePath = true;

    do {
        std::cout << "Enter a source vertex and destination vertex: ";
        std::cin >> sourceVertex >> destinationVertex;
        // Output Shortest Path

        std::cout << "More paths? ";
        std::cin >> morePath;
    } while (isContinue(morePath));

    return 0;
}