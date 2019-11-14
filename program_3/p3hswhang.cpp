#include <iostream>
#include <math.h> // floor() / ceil()
#include <algorithm> // max(), pow()
using namespace std;

int digits(int num); // count digits
int prod(int u, int v); // large integer multiplication

int main() {
  int x, y, alg_result, std_result;

  // Get input
  cout << "Enter two nonnegative integers: ";
  cin >> x >> y;

  // Compute large integer multiplication
  alg_result = prod(x,y);

  // Compute standard multiplication
  std_result = x * y;

  // Test Code digits()
  cout << "X: " << x << " --> has " << digits(x) << " digits." << endl;
  cout << "Y: " << y << " --> has " << digits(y) << " digits." << endl;

  // Print output
  cout << "The result determined using the large integer multiplication algorithm is " << alg_result << endl;
  cout << "The result determined using the standard multiplication algorithm is " << std_result << endl;
  return 0;
}

int digits(int num) {
  int digitCount = 0;

  while (num > 0) {
    num/=10; // Kepp dividing with 10 until 0
    digitCount++;
  }

  return digitCount;
}

int prod(int u, int v) {
  int n = max(digits(u), digits(v));

  if (u == 0 || v == 0)
    return 0;
  else if (n <= 2) // Given threshold = 2 digits
    return u*v;
  else {
    double m = floor(n/2);
    int E = (int)(pow(10,m) + 0.5); // 10^m
    int x = u/E;
    int y = u%E;
    int w = v/E;
    int z = v%E;

    return ((prod(x,w) * ((int)(pow(10,m*2) + 0.5))) + ((prod(x,z) + prod(w,y)) * E) + prod(y,z));
    // Uses +0.5 because pow() intakes double
    // i.e) 5^2 could be 24.99999 resulitng in (int) --solved by adding 0.5
  }
  return 0;
}
