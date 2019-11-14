#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* UTILITY FUNCTIONS */
vector<int> readFile(string fileName);
void printData(vector<int> set);

/* MERGE SORT FUNCTIONS */
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int>& arr);

int main() {
    vector<int> inputTest = readFile("p1data.txt");
    vector <int> tempTest = mergeSort(inputTest);

    printData(tempTest);
}

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
  cout << "================================" << endl;
  cout << "Size: " << set.size() << endl;
  cout << "The contents of the vector is: " << endl;
  for (int i = 0; i < set.size(); i++) {
    if (((i%30) == 0) && (i != 0)) cout << endl << endl; // endl every 30 output
    cout << set[i] << "   ";
  }
  cout << "\n================================" << endl;
}


vector<int> merge(vector<int> left, vector<int> right) {
	size_t ileft = 0, iright = 0;
	vector<int> results;
	while (ileft < left.size() && iright < right.size())
	    if (left[ileft] < right[iright])
	        results.push_back(left[ileft++]);
	    else
	        results.push_back(right[iright++]);
	while (ileft  < left.size() ) results.push_back(left [ileft++ ]);
	while (iright < right.size()) results.push_back(right[iright++]);
	return results;
}

vector<int> mergeSort(vector<int>& arr) {
	if (arr.size() <= 1)
		return arr;
	int len = arr.size() / 2;
	vector<int> left (arr.begin(),       arr.begin() + len);
	vector<int> right(arr.begin() + len, arr.end()        );
	return merge(mergeSort(left), mergeSort(right));
}
