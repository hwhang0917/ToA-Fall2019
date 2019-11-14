#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int main() {
  srand(time(NULL)); // set random time
  vector<int> set;
  int start, end;

  system("cls");
  cout << "Starting integer: "; cin >> start;
  cout << "Ending integer: "; cin >> end;

  if (start > end) { // error input
    cout << "* ERROR: Starting integer should be less than the ending integer!" << endl;
    return 0;
  }

  // Populate vector with integer from start-end
  for (int i=start; i<=end; ++i) set.push_back(i);

  // shuffle vector
  random_shuffle(set.begin(), set.end());

  // fille p1data.txt with shuffled integers
  string fileName = "p1data.txt";
  ofstream file(fileName); // open file output stream

  if (!file) // error if file fails to oepn
    throw system_error(errno, system_category(), "failed to open " + fileName);

  for (int num: set) // populate txt file with newly shuffled integers
    file << num << endl;

  file.close(); // close file

  return 0;
}
