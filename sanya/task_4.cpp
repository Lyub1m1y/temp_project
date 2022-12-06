#include <iostream>
#include <string>
using namespace std;
int main() {
  int p;
  string a, word;
  cin >> word;
  cin >> a;
  p = a.find(word);
  cout << p << endl;
  return 0;
}