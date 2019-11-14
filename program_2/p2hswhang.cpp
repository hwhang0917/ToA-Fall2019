#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

/* ====== UTILITY FUNCTIONS ====== */
vector<int> readFile(string fileName);
void printData(vector<int> set);

/* ====== QUICK SORT FUNCTIONS BASED ON HOARE's ALGORITHM ====== */
void quickSort(vector<int>& set, int low, int high);
void partition(vector<int>& set, int low, int high, int& pivot);


/* ====== MAIN FUNCTION ====== */
int main(int argc, char const *argv[]) {
  system("cls"); // clear command line
  vector<int> set = readFile("p2data.txt"); // hard coded text file name to read integers from
  printData(set);

  quickSort(set, 0, set.size() - 1);
  printData(set);
  return 0;
}

/* ============================================ Acutal functions ============================================ */
vector<int> readFile(string fileName) { // Read integers from file
  vector<int> s;
  int num;
  ifstream file(fileName); // open file input stream

  if (!file) // error if file fails to oepn
    throw system_error(errno, system_category(), "failed to open " + fileName);

  while (file >> num) // loop until getting all the elements from file
    s.push_back(num);

  file.close(); // close filestream

  return s;
}

void printData(vector<int> set) { // Print vector information
  if (set.size() == 0) { // if file is empty
    cout << "EMPTY SET" << endl;
    return;
  }
  cout << "================================" << endl;
  cout << "Size: " << set.size() << endl;
  cout << "The contents of the vector are: " << endl << endl;
  for (int i = 0; i < set.size(); i++) {
    if (((i%30) == 0) && (i != 0)) cout << endl << endl; // endl every 30 output
    cout << set[i] << "   ";
  }
  cout << "\n================================" << endl;
}

// Quick Sort based on Hoare's ALGORITHM
void quickSort(vector<int>& set, int low, int high) {
  int pivot = low;

  if (high > low) {
    partition(set, low, high, pivot);
    quickSort(set, low, pivot - 1);
    quickSort(set, pivot + 1, high);
  }
}
void partition(vector<int>& set, int low, int high, int& pivot) {
  int i, j;
  int pivotItem = set[low];

  j = low;
  for (i = low + 1; i <= high; i ++) {
    if (set[i] < pivotItem) {
      j++;
      swap(set[i], set[j]);
    }
  }

  pivot = j;
  swap(set[low], set[pivot]);
}

/* Pseudo Code
  void quicksort (index low, index high)
  {
    index pivotpoint;
    if (high > low) {
      partition (low, high, pivotpoint);
      quicksort(low, pivotpoint - 1);
      quicksort(pivotpoint + 1, high);
    }
  }

  void partition (index low, index high, index& pivotpoint)
  {
    index i, j;
    keytype pivotitem;

    pivotitem = S[low]; // Choose first item for pivotitem
    j = low;
    for (i = low + 1; i <= high; i++)
      if (S[i] < pivotitem) {
        j++;
        exchange S[i] and S[j];
      }

    pivotpoint = j;
    exchange S[low] and S[pivotpoint]; // Put pivotitem at pivotpoint
  }
*/
