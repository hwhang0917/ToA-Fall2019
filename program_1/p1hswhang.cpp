#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/* UTILITY FUNCTIONS */
vector<int> readFile(string fileName);
void printData(vector<int> set);

/* MERGE SORT FUNCTIONS */
vector<int> mergeSort(vector<int>& set);
vector<int> merge(vector<int> U, vector<int> V);

/* MAIN FUNCTION */
int main() { // main entry point
    vector<int> myVector = readFile("p1data.txt"); // hard coded filename
    printData(mergeSort(myVector)); // print sorted vector
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
  cout << "================================" << endl;
  cout << "Size: " << set.size() << endl;
  cout << "The contents of the vector is: " << endl;
  for (int i = 0; i < set.size(); i++) {
    if (((i%30) == 0) && (i != 0)) cout << endl << endl; // endl every 30 output
    cout << set[i] << "   ";
  }
  cout << "\n================================" << endl;
}

vector<int> mergeSort(vector<int>& set) {
	if (set.size() <= 1) // if set is a single element (or empty set), return itself
		return set;

  // first half vector size
	int half = set.size() / 2;

  // copy elements into U,V vector
	vector<int> U (set.begin(), set.begin() + half); // copy set[0]~set[half] to U
	vector<int> V (set.begin() + half, set.end()); // copy set[half+1]~set[end] to V

  // recursive calling until vector is divded into single element vectors
	return merge(mergeSort(U), mergeSort(V));
}

vector<int> merge(vector<int> U, vector<int> V) {
	size_t n = 0, m = 0; // index to be incremented each time
	vector<int> set; // vector set to store sorted & merged vector of U & V

	while (n < U.size() && m < V.size())// compare both U and V until one vector index overflows
	    if (U[n] < V[m])
	        set.push_back(U[n++]);
	    else
	        set.push_back(V[m++]);

  // Remainder clean up
  while (m < V.size()) set.push_back(V[m++]); // remiander left in V
	while (n < U.size()) set.push_back(U[n++]); // remainder left in U

  // return sorted vector
	return set;
}
